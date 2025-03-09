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
#include "ECS/Components/lbComponent.h"

namespace Lambix
{
    enum class CameraProjectionType
    {
        Perspective = 0,
        Orthographic
    };

    class lbCameraComponent : public lbComponent
    {
    public:
        lbCameraComponent(CameraProjectionType cameraType = CameraProjectionType::Perspective);

        void OnUpdate(lbTimestep ts) override;

        void SetPerspective(float Fov = glm::radians(45.0f), float nearClip = 0.1f, float farClip = 1000.0f);

        void SetOrthographic(float size = 10.0f, float nearClip = -1.0f, float farClip = 1.0f);

        const glm::mat4 &GetViewProjection() const;

    private:
        CameraProjectionType ProjectionType;
        float PerspectiveFOV;
        float OrthographicSize;
        float NearClip;
        float FarClip;
        bool FixedAspectRatio = false; // 固定宽高比

        // 矩阵存储
        glm::mat4 ViewProjectionMatrix = {1.0f};
    };
}
