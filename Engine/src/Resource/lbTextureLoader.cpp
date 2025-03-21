#include "lbTextureLoader.h"
#include "Log/lbLog.h"
#include "lbCache.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Lambix
{
    uint32_t toStbImageFormat(const lbTextureFormat &format)
    {
        switch (format)
        {
        case lbTextureFormat::RGB:
            return STBI_rgb;
        case lbTextureFormat::RGBA:
            return STBI_rgb_alpha;
        default:
            return 0;
        }
    }

    lbTexture2D::Ptr lbTextureLoader::LoadFromFile(const std::filesystem::path &path)
    {
        // 检查缓存
        auto cache = lbCache::Get();
        if (auto cached = cache->GetSource(path.string()))
        {
            return lbTexture2D::Create(cached, GenTextureSpecFromSource(cached));
        }

        // 加载新纹理
        auto source = LoadImageFile(path);
        if (!source)
        {
            LOG_ERROR("Failed to load texture: {}", path.string());
            return nullptr;
        }

        // 更新缓存
        cache->CacheSource(path.string(), source);
        return lbTexture2D::Create(source, GenTextureSpecFromSource(source));
    }

    lbTexture2D::Ptr lbTextureLoader::LoadFromMemory(const void *data, size_t size)
    {
        // 检查缓存
        auto cache = lbCache::Get();
        std::string str = std::string(static_cast<const char *>(data), size);
        if (auto cached = cache->GetSource(str))
        {
            return lbTexture2D::Create(cached, GenTextureSpecFromSource(cached));
        }

        // 创建新的纹理
        int width, height, channels;
        unsigned char *imgData = stbi_load_from_memory(static_cast<const stbi_uc *>(data), static_cast<int>(size),
                                                       &width, &height, &channels, toStbImageFormat(lbTextureFormat::RGBA));

        if (!imgData)
        {
            LOG_ERROR("Failed to load texture from memory");
            return nullptr;
        }

        auto source = CreateSourceFromData(imgData, width, height, 4); // 默认RGBA 四通道
        stbi_image_free(imgData);

        // 缓存
        cache->CacheSource(str, source);

        return lbTexture2D::Create(source, GenTextureSpecFromSource(source));
    }

    lbTexture2D::Ptr lbTextureLoader::CreateSolidColor(uint32_t color)
    {
        //  cache
        auto cache = lbCache::Get();
        std::string str = std::to_string(color);
        if (auto cached = cache->GetSource(str))
        {
            return lbTexture2D::Create(cached, GenTextureSpecFromSource(cached));
        }
        // 创建一个包含 4 字节 RGBA 颜色数据的数组
        std::array<unsigned char, 4> colorData = {
            static_cast<unsigned char>(color & 0xFF),
            static_cast<unsigned char>((color >> 8) & 0xFF),
            static_cast<unsigned char>((color >> 16) & 0xFF),
            static_cast<unsigned char>((color >> 24) & 0xFF)};

        // 明确指定宽度和高度为 1
        uint32_t width = 1;
        uint32_t height = 1;
        int channels = 4; // RGBA 4 通道

        // 创建 lbSource 对象
        auto source = CreateSourceFromData(colorData.data(), width, height, channels);
        cache->CacheSource(str, source);
        // 使用 lbSource 对象创建 lbTexture2D 对象
        return lbTexture2D::Create(source, GenTextureSpecFromSource(source));
    }

    lbTextureCube::Ptr lbTextureLoader::LoadCubeMap(const std::array<std::filesystem::path, 6> &paths)
    {
        std::array<lbSource::Ptr, 6> faceSources;
        uint32_t baseWidth = 0;
        uint32_t baseHeight = 0;

        for (size_t i = 0; i < 6; ++i)
        {
            if (auto cached = lbCache::Get()->GetSource(paths[i].string()))
            {
                faceSources[i] = cached;
            }
            else
            {
                auto source = LoadImageFile(paths[i]);
                if (!source)
                {
                    LOG_ERROR("Failed to load cubemap face: {}", paths[i].string());
                    return nullptr;
                }
                lbCache::Get()->CacheSource(paths[i].string(), source);
                faceSources[i] = source;
            }

            // 首次加载时记录基准尺寸
            if (i == 0)
            {
                baseWidth = faceSources[i]->mWidth;
                baseHeight = faceSources[i]->mHeight;
                if (baseWidth == 0 || baseHeight == 0)
                {
                    LOG_ERROR("Invalid cubemap face size: {}x{}", baseWidth, baseHeight);
                    return nullptr;
                }
            }
            // 后续面尺寸校验
            else if (faceSources[i]->mWidth != baseWidth ||
                     faceSources[i]->mHeight != baseHeight)
            {
                LOG_ERROR("Cubemap face size mismatch: Face {} is {}x{} (Expected {}x{})",
                          i, faceSources[i]->mWidth, faceSources[i]->mHeight,
                          baseWidth, baseHeight);
                return nullptr;
            }
        }

        return lbTextureCube::Create(faceSources, GenTextureSpecFromSource(faceSources[0]));
    }

    lbSource::Ptr lbTextureLoader::LoadImageFile(const std::filesystem::path &path)
    {
        int width, height, channels;
        // stbi_set_flip_vertically_on_load(true);
        stbi_uc *data = stbi_load(path.string().c_str(), &width, &height, &channels, toStbImageFormat(lbTextureFormat::RGBA));

        if (!data)
        {
            return nullptr;
        }

        auto source = CreateSourceFromData(data, width, height, 4); // 默认RGBA 4通道
        stbi_image_free(data);
        return source;
    }

    lbSource::Ptr lbTextureLoader::CreateSourceFromData(const void *data, uint32_t width, uint32_t height, int channels)
    {
        auto source = lbSource::Create();
        source->mWidth = width;
        source->mHeight = height;

        const size_t dataSize = width * height * channels;
        source->mData.resize(dataSize);
        memcpy(source->mData.data(), data, dataSize);

        return source;
    }

    lbTextureSpecification lbTextureLoader::GenTextureSpecFromSource(lbSource::Ptr source)
    {
        lbTextureSpecification spec;
        spec.width = source->mWidth;
        spec.height = source->mHeight;
        return spec;
    }
} // namespace Lambix
