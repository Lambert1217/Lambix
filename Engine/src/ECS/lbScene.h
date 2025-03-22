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

#include "Core/lbCore.h"
#include "entt/entt.hpp"
#include "Utils/lbTimestep.h"
#include "ECS/Components/lbCameraComponent.h"
#include "ECS/Components/lbBasicComponents.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/Components/lbMeshRendererComponent.h"
#include "ECS/System/lbSystemManager.h"
#include "Renderer/lbModel.h"
#include "Renderer/Interfaces/lbFrameBuffer.h"

namespace Lambix
{
    class lbEntity;
    class lbLightSystem;
    class lbCameraSystem;
    class lbScene
    {
    public:
        lbScene();
        ~lbScene();

        std::shared_ptr<lbEntity> CreateEntity(const std::string &name);
        std::shared_ptr<lbEntity> CreateEntityWithUUID(const std::string &name, lbUUID uuid);

        std::shared_ptr<lbEntity> CreateEntityFromModel(const lbModel::Ptr &model);

        void DestroyEntity(std::shared_ptr<lbEntity> entity);

        void Init();
        void OnUpdate(lbTimestep ts);

        entt::registry &GetRegistry() { return m_Registry; }
        std::shared_ptr<lbEntity> GetEntity(entt::entity handle) const;

        // 根据名称获取系统
        lbSystem *GetSystem(const std::string &name) { return m_SystemManager->GetSystem(name); }

        // 获取帧缓冲
        std::shared_ptr<lbFrameBuffer> GetFrameBuffer() const { return m_FrameBuffer; }

    private:
        std::shared_ptr<lbEntity> CreateEntityFromModelHelper(const lbModelNode::Ptr &parentNode, const std::vector<lbMesh::Ptr> &meshes);

        void OnViewportResize(const lbEvent::Ptr &event);

    private:
        friend class lbSceneHierarchyPanel;
        entt::registry m_Registry;
        std::unordered_map<entt::entity, std::shared_ptr<lbEntity>> m_EntityMap;

        // 帧缓存处理
        std::shared_ptr<lbFrameBuffer> m_FrameBuffer;
        struct SceneFrameBufferData
        {
            uint32_t width{0};
            uint32_t height{0};
            bool needUpdate{false};
        } mSceneFrameBufferData;

        // 系统管理
        std::unique_ptr<lbSystemManager> m_SystemManager;
    };
}
