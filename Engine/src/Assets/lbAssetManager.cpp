#include "lbAssetManager.h"
#include "lbAssetImport.h"

namespace Lambix
{
    lbAssetManager::lbAssetManager(const std::filesystem::path &root) : mRootPath(root)
    {
    }

    lbAsset::Ptr lbAssetManager::Load(const std::filesystem::path &path, bool isFullPath)
    {
        std::filesystem::path fullPath = isFullPath ? path : mRootPath / path;
        const lbHashType hash = std::hash<std::string>{}(fullPath.string());
        if (auto it = mAssets.find(hash); it != mAssets.end())
        {
            return it->second;
        }

        // 如果没有在缓存找到，就去文件导入，并加入缓存
        auto result = lbAssetImport::Get()->Import(fullPath, this);
        if (result)
        {
            mAssets.emplace(hash, result);
        }
        return result;
    }
} // namespace Lambix
