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
         * @brief 构造时已经设置根路径，这里使用子路径
         *
         * @param path
         * @return lbAsset::Ptr
         */
        lbAsset::Ptr Load(const std::filesystem::path &path, bool isFullPath = false);

        const std::filesystem::path &GetRoot() const { return mRootPath; }

    private:
        // 项目全部的资产正在使用的资产
        std::unordered_map<lbHashType, lbAsset::Ptr> mAssets;
        // 项目的根路径
        std::filesystem::path mRootPath;
    };
} // namespace Lambix
