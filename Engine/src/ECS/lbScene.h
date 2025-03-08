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
#include "ECS/System/lbSystemManager.h"

namespace Lambix
{
    class lbEntity;
    class lbLightSystem;
    class lbCameraSystem;
    class lbScene
    {
    public:
        lbScene();
        ~lbScene() = default;

        std::shared_ptr<lbEntity> CreateEntity(const std::string &name);
        std::shared_ptr<lbEntity> CreateEntityWithUUID(const std::string &name, lbUUID uuid);

        void DestroyEntity(std::shared_ptr<lbEntity> entity);

        void Init();
        void OnUpdate(lbTimestep ts);
        void OnEvent(Event &e);

        entt::registry &GetRegistry() { return m_Registry; }
        std::shared_ptr<lbEntity> GetEntity(entt::entity handle) const;

        // 根据名称获取系统
        lbSystem *GetSystem(const std::string &name) { return m_SystemManager->GetSystem(name); }

    private:
        void DrawEntity(lbTransformComponent &trans, lbMeshRendererComponent &meshRenderer, lbFlagComponent &flags);

    private:
        entt::registry m_Registry;
        std::unordered_map<entt::entity, std::shared_ptr<lbEntity>> m_EntityMap;

        // 系统管理
        std::unique_ptr<lbSystemManager> m_SystemManager;
    };
}
