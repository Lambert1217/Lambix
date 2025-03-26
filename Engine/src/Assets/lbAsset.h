/**
 * @file lbAsset.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 资产
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Core/lbCore.h"
#include "yaml-cpp/yaml.h"

namespace Lambix
{
    /// @brief 资产的类型
    enum class lbAssetType
    {
        None,
        TextureSource,
        Texture2D
    };

    /// @brief 序列化类型
    enum class lbSerializationFormat
    {
        Binary,
        Yaml
    };

    class lbAssetManager;
    /**
     * @brief 资产类接口
     *
     */
    class lbAsset
    {
    public:
        virtual ~lbAsset() = default;

        /**
         * @brief 获取资产类型
         *
         * @return lbAssetType
         */
        virtual lbAssetType GetType() const = 0;

        /**
         * @brief 资产序列化
         *
         * @param path 目标路径
         * @param fmt 目标格式
         * @return true
         * @return false
         */
        virtual bool Serialize(const std::filesystem::path &path, lbSerializationFormat fmt) = 0;

        /**
         * @brief 资产逆序列化
         *
         * @param path
         * @param manager
         * @return true
         * @return false
         */
        virtual bool Deserialize(const std::filesystem::path &path, lbAssetManager *manager) = 0;

        /**
         * @brief 资源导入
         *
         * @param path
         * @return true
         * @return false
         */
        virtual bool Import(const std::filesystem::path &path) = 0;

        using Ptr = std::shared_ptr<lbAsset>;

        lbHashType hash;                  // 由资产的路径hash得来，全局唯一
        std::filesystem::path sourcePath; // 资源原始路径
    };
} // namespace Lambix
