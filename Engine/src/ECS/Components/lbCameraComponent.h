/**
 * @file lbCameraComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 摄像机组件
 * @date 2025-03-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lambix
{
    enum class CameraProjectionType
    {
        Perspective = 0,
        Orthographic
    };

    struct lbCameraComponent
    {
        CameraProjectionType ProjectionType = CameraProjectionType::Perspective;
        float PerspectiveFOV = glm::radians(45.0f);
        float OrthographicSize = 10.0f;
        float NearClip = 0.1f;
        float FarClip = 1000.0f;
        bool FixedAspectRatio = false; // 固定宽高比

        glm::mat4 GetProjection(float viewportWidth, float viewportHeight) const;
    };
}
