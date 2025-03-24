/**
 * @file lbLight.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "glm/glm.hpp"

#define MAX_DIRECTIONAL_LIGHT 4
#define MAX_POINT_LIGHT 256
#define MAX_SPOT_LIGHT 256

namespace Lambix
{
    // 光源类型
    enum class lbLightType
    {
        None = -1,       // 空类型
        Directional = 0, // 方向光（太阳光）
        Point,           // 点光源（灯泡）
        Spot,            // 聚光灯（舞台灯）
        Area             // 区域光（未来扩展）
    };
    // 光源结构体
    struct lbLight
    {
        glm::vec3 color; // 颜色
        float intensity; // 强度

        virtual lbLightType GetLightType() const { return lbLightType::None; };
        static lbLightType GetStaticType() { return lbLightType::None; }

        lbLight(const glm::vec3 &color, float intensity) : color(color), intensity(intensity) {}
        virtual ~lbLight() = default;
    };

    struct lbDirectionalLight : public lbLight
    {
        glm::vec3 direction; // 光照方向（世界中）

        lbLightType GetLightType() const override { return lbLightType::Directional; }
        static lbLightType GetStaticType() { return lbLightType::Directional; }

        lbDirectionalLight() = delete;
        lbDirectionalLight(const glm::vec3 &direction, const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f)
            : lbLight(color, intensity), direction(direction) {}
    };

    struct lbPointLight : public lbLight
    {
        glm::vec3 position{0.0f}; // 位置
        float MinRange{0.001f};   // 衰减起始距离
        float Range{1.0f};        // 最大作用距离

        lbLightType GetLightType() const override { return lbLightType::Point; }
        static lbLightType GetStaticType() { return lbLightType::Point; }

        lbPointLight() = delete;
        lbPointLight(const glm::vec2 &range, const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f)
            : lbLight(color, intensity), MinRange(range.x), Range(range.y) {}
    };

    struct lbSpotLight : public lbLight
    {
        glm::vec3 position{0.0f}; // 位置
        glm::vec3 direction;      // 方向
        float MinRange = 0.001f;  // 衰减起始距离
        float Range = 1.f;        // 最大作用距离
        float MinAngle = 0.01f;   // 内锥角（角度）
        float Angle = 30.f;       // 外锥角（角度）

        lbLightType GetLightType() const override { return lbLightType::Spot; }
        static lbLightType GetStaticType() { return lbLightType::Spot; }

        lbSpotLight() = delete;
        lbSpotLight(const glm::vec2 &range, const glm::vec2 &angle, const glm::vec3 &color = glm::vec3(1.0f), float intensity = 1.0f)
            : lbLight(color, intensity), MinRange(range.x), Range(range.y), MinAngle(angle.x), Angle(angle.y) {}
    };

    // 单个光源UBO结构
    // 方向光结构
    struct lbDirectionalLightData
    {
        glm::vec3 color;     // 颜色  12B
        float intensity;     // 强度  16B
        glm::vec3 direction; // 方向  16+12
        float padding;       // 填充  32B
    };

    static_assert(sizeof(lbDirectionalLightData) == 32);

    // 点光源结构
    struct lbPointLightData
    {
        glm::vec3 color;    // 颜色  12B
        float intensity;    // 强度  16B
        glm::vec3 position; // 位置  16+12
        float MinRange;     // 衰减起始距离 32
        glm::vec3 padding;  // 44B
        float Range;        // 最大作用距离 44+4B
    };

    static_assert(sizeof(lbPointLightData) == 48);

    // 聚光灯结构
    struct lbSpotLightData
    {
        glm::vec3 color;     // 颜色  12B
        float intensity;     // 强度  16B
        glm::vec3 direction; // 方向  16+12
        float MinRange;      // 衰减起始距离 32B
        glm::vec3 position;  // 位置 32+12
        float Range;         // 最大作用距离 48B
        float MinAngle;      // 内锥角（角度）48+4
        float Angle;         // 外锥角（角度）48+8
        glm::vec2 padding;   // 填充 64B
    };

    static_assert(sizeof(lbSpotLightData) == 64);

    // UBO头部信息
    struct lbLightingHeader
    {
        glm::ivec4 lightCounts; // x:方向光 y:点光 z:聚光 w:总光源数
        glm::vec3 ambient;      // RGB: 环境光颜色
        float ambientIntensity; // 环境光强度 32B
    };

    static_assert(sizeof(lbLightingHeader) == 32);

    // 光源UBO结构
    struct lbLightsData
    {
        lbLightingHeader header;                                         // 32B
        lbDirectionalLightData DirectionalLights[MAX_DIRECTIONAL_LIGHT]; // 4 * 32 = 128B
        lbPointLightData PointLights[MAX_POINT_LIGHT];                   // 256 * 48 = 12288B
        lbSpotLightData SpotLights[MAX_SPOT_LIGHT];                      // 256 * 64 = 16384B
    };

    static_assert(sizeof(lbLightsData) == 32 + 128 + 12288 + 16384);

} // namespace Lambix
