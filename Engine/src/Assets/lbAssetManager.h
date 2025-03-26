/**
 * @file lbAssetManager.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 资产管理  非单例，未来将有项目持有
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbAsset.h"

namespace Lambix
{
    class lbAssetManager
    {
    public:
        // 定义两种函数
        using ImportFunc = std::function<lbAsset::Ptr(const std::filesystem::path &)>;                        // 导入外部资源
        using DeserializeFunc = std::function<lbAsset::Ptr(const std::filesystem::path &, lbAssetManager *)>; // 逆序列化引擎资产

        /// @brief 删除默认的构造函数，必须传入资产根路径
        lbAssetManager() = delete;
        /**
         * @brief 由资产的根路径创建
         *
         * @param root
         */
        lbAssetManager(const std::filesystem::path &root);

        ~lbAssetManager() = default;

        using Ptr = std::shared_ptr<lbAssetManager>;
        static Ptr Create(const std::filesystem::path &root)
        {
            return std::make_shared<lbAssetManager>(root);
        }

        /**
         * @brief 加载资产，外部资源和引擎资源通用
         *
         * @param path
         * @return lbAsset::Ptr
         */
        lbAsset::Ptr Load(const std::filesystem::path &path, bool isFullPath = false);

        const std::filesystem::path &GetRoot() const { return mRootPath; }

        /**
         * @brief 依据文件拓展名注册导入器
         *
         * @tparam T  具体资产类
         * @param extension
         */
        template <typename T>
        void RegisterImporter(const std::string &extension)
        {
            mImporters[extension] = [](const std::filesystem::path &path)
            {
                auto asset = std::make_shared<T>();
                if (asset->Import(path))
                {
                    asset->hash = std::hash<std::string>{}(path.string());
                    asset->sourcePath = path;
                    return asset;
                }
                return std::shared_ptr<T>(nullptr);
            };
        }

        /**
         * @brief 依据文件拓展名注册逆序列化器
         *
         * @tparam T  具体资产类
         * @param extension
         */
        template <typename T>
        void RegisterDeserializer(const std::string &extension)
        {
            mDeserializers[extension] = [](const std::filesystem::path &path, lbAssetManager *manager)
            {
                auto asset = std::make_shared<T>();
                if (asset->Deserialize(path, manager))
                {
                    asset->hash = std::hash<std::string>{}(path.string());
                    asset->sourcePath = path;
                    return asset;
                }
                return std::shared_ptr<T>(nullptr);
            };
        }

    private:
        // 项目全部的资产正在使用的资产
        std::unordered_map<lbHashType, lbAsset::Ptr> mAssets;
        // 项目的根路径
        std::filesystem::path mRootPath;
        // 注册的导入函数
        std::unordered_map<std::string, ImportFunc> mImporters;
        // 注册的逆序列化函数
        std::unordered_map<std::string, DeserializeFunc> mDeserializers;
    };
} // namespace Lambix
