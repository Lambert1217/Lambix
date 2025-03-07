/**
 * @file lbLightComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 光照组件
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <glm/glm.hpp>
#include "ECS/Components/lbComponent.h"

namespace Lambix
{
    enum class LightType
    {
        Directional = 0, // 方向光（太阳光）
        Point,           // 点光源（灯泡）
        Spot,            // 聚光灯（舞台灯）
        Area             // 区域光（未来扩展）
    };

    struct lbLightComponent : public lbComponent
    {
        LightType Type = LightType::Directional;
        glm::vec3 Color = glm::vec3(1.0f); // 光照颜色
        float Intensity = 10.0f;           // 光照强度

        // 点/聚光灯参数
        float Range = 10.0f;
        glm::vec3 Attenuation = glm::vec3(1.0f, 0.09f, 0.032f); // 三参数衰减模型

        // 聚光灯专用
        float InnerAngle = glm::radians(30.0f); // 内锥角
        float OuterAngle = glm::radians(45.0f); // 外锥角

        // 调试标记
        bool Visualize = false; // 是否显示光源图标
    };
}
