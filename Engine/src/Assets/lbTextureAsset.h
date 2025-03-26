/**
 * @file lbTextureAsset.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 纹理资产
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbTextureSourceAsset.h"
#include "Renderer/Interfaces/lbTexture.h"

namespace Lambix
{
    class lbTexture2DAsset : public lbAsset
    {
    public:
        lbTexture2DAsset() = default;

        /**
         * @brief 注意：这里构造不能生成hash，sourcePath，用于创建新的纹理时，创建完成立即序列化为文件，通过管理器加载使用并生成hash
         *
         * @param source
         * @param spec
         */
        lbTexture2DAsset(const lbTextureSourceAsset::Ptr &source, const lbTextureSpecification &spec = {});
        ~lbTexture2DAsset() = default;

        using Ptr = std::shared_ptr<lbTexture2DAsset>;
        static Ptr Create()
        {
            return std::make_shared<lbTexture2DAsset>();
        }
        static Ptr Create(const lbTextureSourceAsset::Ptr &source, const lbTextureSpecification &spec = {})
        {
            return std::make_shared<lbTexture2DAsset>(source, spec);
        }

        lbAssetType GetType() const override { return lbAssetType::Texture2D; }

        bool Serialize(const std::filesystem::path &path, lbSerializationFormat fmt) override;

        bool Deserialize(const std::filesystem::path &path, lbAssetManager *manager) override;

        bool Import(const std::filesystem::path &path) override;

        uint32_t GetRendererID() const { return mTexture->GetRendererID(); }

    private:
        lbTextureSpecification mSpec;
        lbTextureSourceAsset::Ptr mSource;
        lbTexture2D::Ptr mTexture{nullptr};
    };

    void SerializeTextureSpecification(YAML::Emitter &out, const lbTextureSpecification &spec);

    lbTextureSpecification DeserializeTextureSpecification(const YAML::Node &node);

    std::string lbTextureWrappingToString(const Lambix::lbTextureWrapping &wrapping);

    std::string lbTextureFilterToString(const Lambix::lbTextureFilter &filter);

    std::string lbTextureFormatToString(const Lambix::lbTextureFormat &format);

    std::string lbDataTypeToString(const Lambix::lbDataType &dataType);

    lbTextureWrapping StringToTextureWrapping(const std::string &str);

    lbTextureFilter StringToTextureFilter(const std::string &str);

    lbTextureFormat StringToTextureFormat(const std::string &str);

    lbDataType StringToDataType(const std::string &str);
} // namespace Lambix
