/**
 * @file lbCameraSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 摄像机系统
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbSystem.h"
#include "Events/lbEvent.h"
#include "glm/glm.hpp"

namespace Lambix
{
    class lbEntity;
    class lbCameraSystem : public lbSystem
    {
    public:
        explicit lbCameraSystem(lbScene *scene);
        ~lbCameraSystem() override;

        void Init() override;
        void OnUpdate(lbTimestep ts) override;

        // 主摄像机管理
        std::shared_ptr<lbEntity> GetPrimaryCameraEntity() { return m_PrimaryCameraEntity; }
        void SetPrimaryCamera(std::shared_ptr<lbEntity> cameraEntity) { m_PrimaryCameraEntity = cameraEntity; }

        // 视口管理
        void SetViewportSize(float width, float height);
        float GetViewportWidth() const { return viewportWidth; }
        float GetViewportHeight() const { return viewportHeight; }

        struct lbCameraController
        {
            // 是否能操控
            bool flag{false};
            // 摄像机指针
            std::shared_ptr<lbEntity> camera{nullptr};
            // 位移
            float speed{5.0f}; // 位移速度
            // 旋转
            float rotationSpeed{5.0f}; // 旋转灵敏度
            float m_LastMouseX{-1.0f}; // 上一帧鼠标X坐标
            float m_LastMouseY{-1.0f}; // 上一帧鼠标Y坐标

            lbCameraController();
            lbCameraController(const std::shared_ptr<lbEntity> &cameraEntity);
            ~lbCameraController();

            void OnUpdate(lbTimestep ts);
        };

    private:
        void OnViewportResize(const lbEvent::Ptr &event);
        void OnViewportReadyForCameraControl(const lbEvent::Ptr &event);

    private:
        friend class lbCameraComponent;
        std::shared_ptr<lbEntity> m_PrimaryCameraEntity;
        float viewportWidth{1}, viewportHeight{1};
        // camera control
        lbCameraController m_PrimaryCameraController{};
    };
} // namespace Lambix
