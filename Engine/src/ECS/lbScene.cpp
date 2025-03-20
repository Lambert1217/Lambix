#include "ECS/lbScene.h"
#include "ECS/lbEntity.h"
#include "Renderer/lbRendererCommand.h"
#include "ECS/System/lbLightSystem.h"
#include "ECS/System/lbTransformSystem.h"
#include "ECS/System/lbCameraSystem.h"
#include "ECS/System/lbRendererSystem.h"
#include "lbScene.h"

namespace Lambix
{
    lbScene::lbScene() : m_SystemManager(std::make_unique<lbSystemManager>())
    {
    }
    std::shared_ptr<lbEntity> lbScene::CreateEntity(const std::string &name)
    {
        return CreateEntityWithUUID(name, GenUUID());
    }

    std::shared_ptr<lbEntity> lbScene::CreateEntityWithUUID(const std::string &name, lbUUID uuid)
    {
        std::shared_ptr<lbEntity> entity = std::make_shared<lbEntity>(m_Registry.create(), this);
        // ID组件
        {
            entity->AddComponent<lbIdentityComponent>(uuid, name);
        }
        // 父子组件
        {
            entity->AddComponent<lbParentComponent>();
            entity->AddComponent<lbChildrenComponent>();
        }
        // 变换组件
        {
            auto &transformComp = entity->AddComponent<lbTransformComponent>();
        }
        // 标志组件
        {
            auto &FlagComponent = entity->AddComponent<lbFlagComponent>();
            FlagComponent.SetRenderable(false);
        }
        m_EntityMap[entity->GetHandle()] = entity;
        return entity;
    }

    void lbScene::DestroyEntity(std::shared_ptr<lbEntity> entity)
    {
        if (!entity || !m_EntityMap.count(entity->GetHandle()))
            return;

        // 递归销毁子实体
        if (auto *childrenComp = m_Registry.try_get<lbChildrenComponent>(entity->GetHandle()))
        {
            auto children = childrenComp->m_Children; // 复制列表避免迭代时修改
            for (auto childHandle : children)
            {
                if (auto it = m_EntityMap.find(childHandle); it != m_EntityMap.end())
                {
                    DestroyEntity(it->second);
                }
            }
        }

        // 处理父节点关系
        if (auto *parentComp = m_Registry.try_get<lbParentComponent>(entity->GetHandle()))
        {
            if (auto parentIt = m_EntityMap.find(parentComp->m_Parent); parentIt != m_EntityMap.end())
            {
                auto &parentChildren = parentIt->second->GetComponent<lbChildrenComponent>();
                parentChildren.m_Children.erase(
                    std::remove(parentChildren.m_Children.begin(),
                                parentChildren.m_Children.end(),
                                entity->GetHandle()),
                    parentChildren.m_Children.end());
            }
        }

        // 清理注册表
        m_Registry.destroy(entity->GetHandle());
        m_EntityMap.erase(entity->GetHandle());
    }

    void lbScene::Init()
    {
        // 创建各个系统
        // 变换系统 用于更新实体的TransformComponent  优先级 1
        auto transformSystem = m_SystemManager->CreateSystem<lbTransformSystem>(this);
        transformSystem->Init();
        // 摄像机系统，用于管理摄像机， 优先级 2
        auto cameraSystem = m_SystemManager->CreateSystem<lbCameraSystem>(this);
        cameraSystem->Init();
        // 光源系统 用于更新实体的LightComponent，收集光源上传到UBO  优先级 3
        auto lightSystem = m_SystemManager->CreateSystem<lbLightSystem>(this);
        lightSystem->Init();
        // 渲染系统
        auto rendererSystem = m_SystemManager->CreateSystem<lbRendererSystem>(this);
        rendererSystem->Init();
    }

    void lbScene::OnUpdate(lbTimestep ts)
    {
        m_SystemManager->OnUpdate(ts);
    }

    std::shared_ptr<lbEntity> lbScene::GetEntity(entt::entity handle) const
    {
        if (handle == entt::null)
            return nullptr;
        if (auto it = m_EntityMap.find(handle); it != m_EntityMap.end())
        {
            return it->second;
        }
        return nullptr;
    }
}