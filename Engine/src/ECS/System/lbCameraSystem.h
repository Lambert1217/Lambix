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

namespace Lambix
{
    class lbEntity;
    class lbCameraSystem : public lbSystem
    {
    public:
        explicit lbCameraSystem(lbScene *scene);

        void Init() override;
        void OnUpdate(lbTimestep ts) override;

        // 主摄像机管理
        std::shared_ptr<lbEntity> GetPrimaryCameraEntity() { return m_PrimaryCameraEntity; }
        void SetPrimaryCamera(std::shared_ptr<lbEntity> cameraEntity) { m_PrimaryCameraEntity = cameraEntity; }

        // 视口管理
        void SetViewportSize(float width, float height);
        float GetViewportWidth() const { return viewportWidth; }
        float GetViewportHeight() const { return viewportHeight; }

    private:
        friend class lbCameraComponent;
        std::shared_ptr<lbEntity> m_PrimaryCameraEntity;
        float viewportWidth{1}, viewportHeight{1};
    };
} // namespace Lambix
