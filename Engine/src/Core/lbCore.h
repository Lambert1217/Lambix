/**
 ***************************************************************
 * @file            : lbCore.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{
    // UUID
    using lbUUID = uint64_t;

    static lbUUID GenUUID()
    {
        static lbUUID s_UUID = 0;
        return s_UUID++;
    }
    // RenderState 相关
    enum class FrontFace
    {
        Clockwise,       // 顺时针
        CounterClockwise // 逆时针
    };

    enum class PolygonMode
    {
        Fill,
        Line,
        Point
    };

    enum class BlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha
    };

    enum class DepthFunc
    {
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        Always
    };

    enum class CullFace
    {
        Front,
        Back,
        FrontAndBack
    };

    enum class DrawMode
    {
        Points,        // 点渲染 GL_POINTS
        Lines,         // 独立线段 GL_LINES
        LineStrip,     // 连续折线 GL_LINE_STRIP
        LineLoop,      // 闭合折线 GL_LINE_LOOP
        Triangles,     // 独立三角形 GL_TRIANGLES
        TriangleStrip, // 三角带 GL_TRIANGLE_STRIP
        TriangleFan    // 三角扇 GL_TRIANGLE_FAN
    };

    struct RenderState
    {
        // Depth
        bool depthTest = true;
        DepthFunc depthFunc = DepthFunc::Less;
        bool depthWrite = true;

        // Blend
        bool blendEnable = true;
        BlendFactor srcFactor = BlendFactor::SrcAlpha;
        BlendFactor dstFactor = BlendFactor::OneMinusSrcAlpha;

        // Face culling
        bool cullEnable = true;
        CullFace cullFace = CullFace::Back;
        FrontFace frontFace = FrontFace::CounterClockwise;

        // Polygon mode
        PolygonMode polygonMode = PolygonMode::Fill;

        // DrawMode
        DrawMode drawMode = DrawMode::Triangles;
    };

    // 顶点属性相关  VBO

    // opengl或者其他图形api，将buffer分成了两种类型（在咱们使用范围内），
    // static,在创建VBO的时候，会将内存分配到GPU端，适合一次性传输，不经常更改的数据
    // dynamic，在创建VBO的时候，会将内存分配到CPU端（大概率），适合多次频繁的更改
    enum class lbBufferAllocType
    {
        StaticDrawBuffer,
        DynamicDrawBuffer
    };

    /**
     * @brief 枚举buffer类型
     *
     */
    enum class lbBufferType
    {
        ArrayBuffer,
        IndexBuffer
    };

    enum class lbDataType
    {
        UnsignedByteType,
        ByteType,
        Int32Type,
        UInt32Type,
        FloatType
    };

    struct lbRange
    {
        int32_t mOffset{0};
        int32_t mCount{-1};
    };

    template <typename T>
    static lbDataType tolbDataType()
    {
        if (typeid(T) == typeid(float))
        {
            return lbDataType::FloatType;
        }

        if (typeid(T) == typeid(int))
        {
            return lbDataType::Int32Type;
        }

        if (typeid(T) == typeid(char))
        {
            return lbDataType::ByteType;
        }

        if (typeid(T) == typeid(unsigned char))
        {
            return lbDataType::UnsignedByteType;
        }

        if (typeid(T) == typeid(uint32_t))
        {
            return lbDataType::UInt32Type;
        }

        return lbDataType::FloatType;
    }

    static uint32_t GetSize(const lbDataType &value)
    {
        switch (value)
        {
        case lbDataType::ByteType:
            return sizeof(char);
        case lbDataType::FloatType:
            return sizeof(float);
        case lbDataType::Int32Type:
            return sizeof(int);
        case lbDataType::UInt32Type:
            return sizeof(uint32_t);
        case lbDataType::UnsignedByteType:
            return sizeof(unsigned char);
        default:
            return 0;
        }
    }

    // VAO
    // attributes
    static const std::unordered_map<std::string, uint32_t> LOCATION_MAP = {
        {"a_Position", 0},
        {"a_Normal", 1},
        {"a_Color", 2},
        {"a_UV", 3},
        {"a_SkinIndex", 4},
        {"a_SkinWeight", 5},
        {"a_Tangent", 6},
        {"a_Bitangent", 7}};

    // Texture
    enum class lbTextureWrapping
    {
        RepeatWrapping,
        ClampToEdgeWrapping,
        ClampToBorder,
        MirroredRepeatWrapping,
    };

    enum class lbTextureFilter
    {
        LinearFilter,
        NearestFilter,
        LinearMipmapLinear
    };

    enum class lbTextureUsage
    {
        SamplerTexture,
        RenderTargetTexture
    };

    enum class lbTextureFormat
    {
        RGB,
        RGBA,
        DepthFormat,
        DepthStencilFormat
    };

    enum class lbTextureType
    {
        Texture2D,
        TextureCubeMap
    };
}
