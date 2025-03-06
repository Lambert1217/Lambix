/**
 * @file lbScene.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 场景类
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Utils/lbUUID.h"
#include "entt/entt.hpp"
#include "Utils/lbTimestep.h"
#include "ECS/Components/lbCameraComponent.h"
#include "ECS/Components/lbBasicComponents.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/Components/lbMeshRendererComponent.h"

namespace Lambix
{
    class lbEntity;
    class lbLightSystem;
    class lbScene
    {
    public:
        lbScene();
        ~lbScene() = default;

        std::shared_ptr<lbEntity> CreateEntity(const std::string &name);
        std::shared_ptr<lbEntity> CreateEntityWithUUID(const std::string &name, lbUUID uuid);

        void DestroyEntity(std::shared_ptr<lbEntity> entity);

        void OnUpdate(lbTimestep ts);

        entt::registry &GetRegistry() { return m_Registry; }
        const std::unordered_map<entt::entity, std::shared_ptr<lbEntity>> &GetEntityMap() const { return m_EntityMap; }

        // 主摄像机管理
        std::shared_ptr<lbEntity> GetPrimaryCameraEntity() { return m_PrimaryCameraEntity; }
        void SetPrimaryCamera(std::shared_ptr<lbEntity> cameraEntity) { m_PrimaryCameraEntity = cameraEntity; }

        // 视口管理
        void SetViewportSize(float width, float height);
        float GetViewportWidth() const { return viewportWidth; }
        float GetViewportHeight() const { return viewportHeight; }

    private:
        void DrawEntity(lbTransformComponent &trans, lbMeshRendererComponent &meshRenderer, lbFlagComponent &flags);

    private:
        entt::registry m_Registry;
        std::unordered_map<entt::entity, std::shared_ptr<lbEntity>> m_EntityMap;

        // 主摄像机实体
        std::shared_ptr<lbEntity> m_PrimaryCameraEntity;
        float viewportWidth{1}, viewportHeight{1};

        // 光照系统
        std::shared_ptr<lbLightSystem> m_LightSystem;
    };
}
