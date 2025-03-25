/**
 * @file lbAssetImport.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 资产导入器 单例
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbAsset.h"
#include "Utils/lbSingleton.h"
#include "Log/lbLog.h"
#include "lbAssetManager.h"

namespace Lambix
{
    class lbAssetImport : public lbSingleton<lbAssetImport>
    {
    public:
        /// @brief 资产导入函数
        using ImportFunc = std::function<lbAsset::Ptr(const std::filesystem::path &path, lbAssetManager *)>;

        lbAssetImport();

        /**
         * @brief 依据文件拓展名注册导入器
         *
         * @tparam T  具体资产类
         * @param extension
         */
        template <typename T>
        void RegisterImporter(const std::string &extension)
        {
            mImporters[extension] = [](const std::filesystem::path &path, lbAssetManager *manager)
            {
                auto asset = std::make_shared<T>();
                if (asset->Import(path, manager))
                {
                    asset->hash = std::hash<std::string>{}(path.string());
                    asset->sourcePath = path;
                    return asset;
                }
                return std::shared_ptr<T>(nullptr);
            };
        }

        /**
         * @brief 导入资源
         *
         * @param path
         * @return lbAsset::Ptr
         */
        lbAsset::Ptr Import(const std::filesystem::path &path, lbAssetManager *assetManager)
        {
            auto ext = path.extension().string().substr(1);
            if (mImporters.find(ext) != mImporters.end())
            {
                return mImporters[ext](path, assetManager);
            }
            return nullptr;
        }

    private:
        /// @brief 所有注册的导入器
        std::unordered_map<std::string, ImportFunc> mImporters;
    };
} // namespace Lambix
