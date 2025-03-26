#include "lbTextureAsset.h"
#include "lbAssetManager.h"
#include "Log/lbLog.h"

namespace Lambix
{
    lbTexture2DAsset::lbTexture2DAsset(const lbTextureSourceAsset::Ptr &source, const lbTextureSpecification &spec)
        : mSource(source), mSpec(spec)
    {
        mSpec.width = mSource->GetWidth();
        mSpec.height = mSource->GetHeight();
        // 仅为了转化ltex，就不生成纹理了
    }

    bool lbTexture2DAsset::Serialize(const std::filesystem::path &path, lbSerializationFormat fmt)
    {
        if (fmt == lbSerializationFormat::Yaml)
        {
            YAML::Emitter out;
            out << YAML::BeginMap;
            out << YAML::Key << "SourcePath" << YAML::Value << mSource->sourcePath.string();
            SerializeTextureSpecification(out, mSpec);
            out << YAML::EndMap;

            std::ofstream file(path);
            file << out.c_str();
            return true;
        }
        LOG_WARN("lbTexture2DAsset: Binary serialization is not supported for the time being.");
        return false;
    }

    bool lbTexture2DAsset::Deserialize(const std::filesystem::path &path, lbAssetManager *manager)
    {
        YAML::Node node = YAML::LoadFile(path.string());
        std::string sourcePathStr = node["SourcePath"].as<std::string>();
        mSource = std::static_pointer_cast<lbTextureSourceAsset>(manager->Load(sourcePathStr, true));
        const YAML::Node specNode = node["Spec"];
        mSpec = DeserializeTextureSpecification(specNode);
        mTexture = lbTexture2D::Create(mSource->GetData(), mSpec);
        return true;
    }

    bool lbTexture2DAsset::Import(const std::filesystem::path &path)
    {
        return false;
    }

    void SerializeTextureSpecification(YAML::Emitter &out, const lbTextureSpecification &spec)
    {
        out << YAML::Key << "Spec" << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "width" << YAML::Value << spec.width;
        out << YAML::Key << "height" << YAML::Value << spec.height;
        out << YAML::Key << "dataType" << YAML::Value << lbDataTypeToString(spec.dataType);
        out << YAML::Key << "wrapS" << YAML::Value << lbTextureWrappingToString(spec.wrapS);
        out << YAML::Key << "wrapT" << YAML::Value << lbTextureWrappingToString(spec.wrapT);
        out << YAML::Key << "wrapR" << YAML::Value << lbTextureWrappingToString(spec.wrapR);
        out << YAML::Key << "magFilter" << YAML::Value << lbTextureFilterToString(spec.magFilter);
        out << YAML::Key << "minFilter" << YAML::Value << lbTextureFilterToString(spec.minFilter);
        out << YAML::Key << "format" << YAML::Value << lbTextureFormatToString(spec.format);
        out << YAML::Key << "internalFormat" << YAML::Value << lbTextureFormatToString(spec.internalFormat);
        out << YAML::EndMap;
    }

    lbTextureSpecification DeserializeTextureSpecification(const YAML::Node &node)
    {
        lbTextureSpecification spec;
        spec.width = node["width"].as<uint32_t>();
        spec.height = node["height"].as<uint32_t>();
        spec.dataType = StringToDataType(node["dataType"].as<std::string>());
        spec.wrapS = StringToTextureWrapping(node["wrapS"].as<std::string>());
        spec.wrapT = StringToTextureWrapping(node["wrapT"].as<std::string>());
        spec.wrapR = StringToTextureWrapping(node["wrapR"].as<std::string>());
        spec.magFilter = StringToTextureFilter(node["magFilter"].as<std::string>());
        spec.minFilter = StringToTextureFilter(node["minFilter"].as<std::string>());
        spec.format = StringToTextureFormat(node["format"].as<std::string>());
        spec.internalFormat = StringToTextureFormat(node["internalFormat"].as<std::string>());
        return spec;
    }

    // 将枚举类型 lbTextureWrapping 转换为字符串
    std::string lbTextureWrappingToString(const Lambix::lbTextureWrapping &wrapping)
    {
        switch (wrapping)
        {
        case Lambix::lbTextureWrapping::RepeatWrapping:
            return "RepeatWrapping";
        case Lambix::lbTextureWrapping::ClampToEdgeWrapping:
            return "ClampToEdgeWrapping";
        case Lambix::lbTextureWrapping::ClampToBorder:
            return "ClampToBorder";
        case Lambix::lbTextureWrapping::MirroredRepeatWrapping:
            return "MirroredRepeatWrapping";
        }
        return "";
    }

    // 将枚举类型 lbTextureFilter 转换为字符串
    std::string lbTextureFilterToString(const Lambix::lbTextureFilter &filter)
    {
        switch (filter)
        {
        case Lambix::lbTextureFilter::LinearFilter:
            return "LinearFilter";
        case Lambix::lbTextureFilter::NearestFilter:
            return "NearestFilter";
        case Lambix::lbTextureFilter::LinearMipmapLinear:
            return "LinearMipmapLinear";
        }
        return "";
    }

    // 将枚举类型 lbTextureFormat 转换为字符串
    std::string lbTextureFormatToString(const Lambix::lbTextureFormat &format)
    {
        switch (format)
        {
        case Lambix::lbTextureFormat::RGB:
            return "RGB";
        case Lambix::lbTextureFormat::RGBA:
            return "RGBA";
        case Lambix::lbTextureFormat::DepthFormat:
            return "DepthFormat";
        case Lambix::lbTextureFormat::DepthStencilFormat:
            return "DepthStencilFormat";
        }
        return "";
    }

    // 将枚举类型 lbDataType 转换为字符串
    std::string lbDataTypeToString(const Lambix::lbDataType &dataType)
    {
        switch (dataType)
        {
        case Lambix::lbDataType::UnsignedByteType:
            return "UnsignedByteType";
        case Lambix::lbDataType::ByteType:
            return "ByteType";
        case Lambix::lbDataType::Int32Type:
            return "Int32Type";
        case Lambix::lbDataType::UInt32Type:
            return "UInt32Type";
        case Lambix::lbDataType::FloatType:
            return "FloatType";
        }
        return "";
    }

    // 将字符串转换为 lbTextureWrapping 枚举
    lbTextureWrapping StringToTextureWrapping(const std::string &str)
    {
        if (str == "RepeatWrapping")
        {
            return lbTextureWrapping::RepeatWrapping;
        }
        else if (str == "ClampToEdgeWrapping")
        {
            return lbTextureWrapping::ClampToEdgeWrapping;
        }
        else if (str == "ClampToBorder")
        {
            return lbTextureWrapping::ClampToBorder;
        }
        else if (str == "MirroredRepeatWrapping")
        {
            return lbTextureWrapping::MirroredRepeatWrapping;
        }
        // 处理错误情况，这里简单返回默认值
        return lbTextureWrapping::RepeatWrapping;
    }

    // 将字符串转换为 lbTextureFilter 枚举
    lbTextureFilter StringToTextureFilter(const std::string &str)
    {
        if (str == "LinearFilter")
        {
            return lbTextureFilter::LinearFilter;
        }
        else if (str == "NearestFilter")
        {
            return lbTextureFilter::NearestFilter;
        }
        else if (str == "LinearMipmapLinear")
        {
            return lbTextureFilter::LinearMipmapLinear;
        }
        // 处理错误情况，这里简单返回默认值
        return lbTextureFilter::LinearFilter;
    }

    // 将字符串转换为 lbTextureFormat 枚举
    lbTextureFormat StringToTextureFormat(const std::string &str)
    {
        if (str == "RGB")
        {
            return lbTextureFormat::RGB;
        }
        else if (str == "RGBA")
        {
            return lbTextureFormat::RGBA;
        }
        else if (str == "DepthFormat")
        {
            return lbTextureFormat::DepthFormat;
        }
        else if (str == "DepthStencilFormat")
        {
            return lbTextureFormat::DepthStencilFormat;
        }
        // 处理错误情况，这里简单返回默认值
        return lbTextureFormat::RGBA;
    }

    // 将字符串转换为 lbDataType 枚举
    lbDataType StringToDataType(const std::string &str)
    {
        if (str == "UnsignedByteType")
        {
            return lbDataType::UnsignedByteType;
        }
        else if (str == "ByteType")
        {
            return lbDataType::ByteType;
        }
        else if (str == "Int32Type")
        {
            return lbDataType::Int32Type;
        }
        else if (str == "UInt32Type")
        {
            return lbDataType::UInt32Type;
        }
        else if (str == "FloatType")
        {
            return lbDataType::FloatType;
        }
        // 处理错误情况，这里简单返回默认值
        return lbDataType::UnsignedByteType;
    }

} // namespace Lambix
