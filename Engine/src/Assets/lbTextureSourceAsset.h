/**
 * @file lbTextureSourceAsset.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 纹理数据资产, 仅支持从图像导入数据存在内存，没压缩，暂不支持序列化
 *         存在的意义在于可以用资产管理器管理图像的数据，让多个纹理可以共用数据，无需反复读入
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbAsset.h"

namespace Lambix
{
    class lbTextureSourceAsset : public lbAsset
    {
    public:
        lbTextureSourceAsset() = default;
        ~lbTextureSourceAsset() = default;

        using Ptr = std::shared_ptr<lbTextureSourceAsset>;
        static Ptr Create()
        {
            return std::make_shared<lbTextureSourceAsset>();
        }

        lbAssetType GetType() const override { return lbAssetType::TextureSource; }

        bool Serialize(const std::filesystem::path &path, lbSerializationFormat fmt) override { return false; }

        bool Deserialize(const std::filesystem::path &path, lbAssetManager *manager) override { return false; }

        bool Import(const std::filesystem::path &path) override;

        uint16_t GetWidth() const { return mWidth; }

        uint16_t GetHeight() const { return mHeight; }

        const std::vector<std::byte> &GetData() const { return mData; }

    private:
        uint16_t mWidth;
        uint16_t mHeight;
        std::vector<std::byte> mData;
    };
} // namespace Lambix
