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

// 处理事件大类枚举，使得可以组合
#define BIT(x) (1 << x)

// 绑定函数
#define LB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Lambix
{
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
}
