#include "lbAssetManager.h"
#include "lbTextureSourceAsset.h"
#include "lbTextureAsset.h"
#include "Log/lbLog.h"

namespace Lambix
{
    lbAssetManager::lbAssetManager(const std::filesystem::path &root) : mRootPath(root)
    {
        // 注册导入器
        RegisterImporter<lbTextureSourceAsset>("jpg");
        RegisterImporter<lbTextureSourceAsset>("png");
        // 注册逆序化器
        RegisterDeserializer<lbTexture2DAsset>("ltex");
    }

    lbAsset::Ptr lbAssetManager::Load(const std::filesystem::path &path, bool isFullPath)
    {
        // 先去cache寻找
        std::filesystem::path fullPath = isFullPath ? path : mRootPath / path;
        const lbHashType hash = std::hash<std::string>{}(fullPath.string());
        if (auto it = mAssets.find(hash); it != mAssets.end())
        {
            return it->second;
        }
        // 如果没有在缓存找到，就去文件导入，并加入缓存
        lbAsset::Ptr asset;
        std::string extension = fullPath.extension().string().substr(1);
        if (auto it = mDeserializers.find(extension); it != mDeserializers.end())
        {
            asset = mDeserializers[extension](fullPath, this);
        }
        else if (auto it = mImporters.find(extension); it != mImporters.end())
        {
            asset = mImporters[extension](fullPath);
        }
        if (asset)
        {
            mAssets.emplace(hash, asset);
            return asset;
        }
        LOG_ERROR("Unregistered file - extension: {}", extension);
        return lbAsset::Ptr(nullptr);
    }
} // namespace Lambix
