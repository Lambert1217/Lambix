#include "lbTextureSourceAsset.h"
#include "Log/lbLog.h"
#include "stb_image.h"

namespace Lambix
{
    bool lbTextureSourceAsset::Import(const std::filesystem::path &path, lbAssetManager *manager)
    {
        int width, height, channels;
        // 引擎默认全部转成 RGBA
        stbi_uc *data = stbi_load(path.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (!data)
        {
            LOG_ERROR("The texture source reading failed. {}", path.string());
            return false;
        }
        // 文件读取成功，开始赋值
        mWidth = width;
        mHeight = height;
        // 拷贝data
        const size_t dataSize = mWidth * mHeight * 4;
        mData.resize(dataSize);
        memcpy(mData.data(), data, dataSize);
        // 释放data
        stbi_image_free(data);
        return true;
    }

} // namespace Lambix
