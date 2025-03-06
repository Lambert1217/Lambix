/**
 * @file lbLightingDefines.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 定义光照数据
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include <glm/glm.hpp>

#define MAX_DIRECTIONAL_LIGHT 4
#define MAX_POINT_LIGHT 16
#define MAX_SPOT_LIGHT 8

namespace Lambix
{
    // 基础光照参数
    struct lbBaseLightData
    {
        glm::vec4 color; // RGB: 颜色, A: 强度
    };

    // 方向光结构
    struct lbDirectionalLightData
    {
        glm::vec4 direction; // XYZ: 方向, W: 未使用
        lbBaseLightData base;
    };

    // 点光源结构
    struct lbPointLightData
    {
        glm::vec4 position; // XYZ: 位置, W: 范围
        lbBaseLightData base;
        glm::vec4 attenuation; // x: 常数衰减, y: 线性衰减, z: 二次衰减
    };

    // 聚光灯结构
    struct lbSpotLightData
    {
        glm::vec4 position;  // XYZ: 位置, W: 范围
        glm::vec4 direction; // XYZ: 方向, W: 内锥角余弦值
        lbBaseLightData base;
        glm::vec4 spotParams; // x: 外锥角余弦值, y: 衰减指数
    };

    // UBO头部信息
    struct lbLightingHeader
    {
        glm::ivec4 lightCounts; // x:方向光 y:点光 z:聚光 w:总光源数
        glm::vec4 ambient;      // RGB: 环境光颜色, A: 强度
    };

    struct lbLightData
    {
        lbLightingHeader header;
        lbDirectionalLightData directionalLights[MAX_DIRECTIONAL_LIGHT];
        lbPointLightData pointLights[MAX_POINT_LIGHT];
        lbSpotLightData spotLights[MAX_SPOT_LIGHT];
    };
}
