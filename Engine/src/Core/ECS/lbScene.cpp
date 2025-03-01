#include "Core/ECS/lbScene.h"
#include "Core/ECS/lbEntity.h"
#include "Core/ECS/Components/lbBasicComponents.h"
#include "Core/ECS/Components/lbTransformComponent.h"

namespace Lambix
{
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
        // 变换组件
        {
            auto &transformComp = entity->AddComponent<lbTransformComponent>();
            transformComp.LinkToEntity(entity);
        }

        m_EntityMap[*entity] = entity;
        return entity;
    }

    void lbScene::DestroyEntity(std::shared_ptr<lbEntity> entity)
    {
        if (!entity || !m_EntityMap.count(*entity))
            return;

        // 递归销毁子实体
        if (auto *childrenComp = m_Registry.try_get<lbChildrenComponent>(*entity))
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
        if (auto *parentComp = m_Registry.try_get<lbParentComponent>(*entity))
        {
            if (auto parentIt = m_EntityMap.find(parentComp->m_Parent);
                parentIt != m_EntityMap.end())
            {
                auto &parentChildren = parentIt->second->GetComponent<lbChildrenComponent>();
                parentChildren.m_Children.erase(
                    std::remove(parentChildren.m_Children.begin(),
                                parentChildren.m_Children.end(),
                                *entity),
                    parentChildren.m_Children.end());
            }
        }

        // 清理注册表
        m_Registry.destroy(*entity);
        m_EntityMap.erase(*entity);
    }

    void lbScene::OnUpdate(lbTimestep ts)
    {
        UpdateTransforms();
    }

    void lbScene::PrintEntityHierarchy(entt::entity entity, int indentLevel)
    {
        const std::string indent(indentLevel * 2, ' ');

        // 获取实体基本信息
        auto &identity = m_Registry.get<lbIdentityComponent>(entity);
        std::string parentInfo = "";

        // 获取父实体信息
        if (auto *parentComp = m_Registry.try_get<lbParentComponent>(entity))
        {
            if (auto parentIt = m_EntityMap.find(parentComp->m_Parent);
                parentIt != m_EntityMap.end())
            {
                parentInfo = " -> Parent: " + parentIt->second->GetName();
            }
        }

        // 输出带缩进的实体信息
        LOG_TRACE("{0}[{1}] {2} (UUID: {3}){4}",
                  indent,
                  (uint32_t)entity,
                  identity.m_Name,
                  identity.m_UUID,
                  parentInfo);

        // 递归输出子实体
        if (auto *childrenComp = m_Registry.try_get<lbChildrenComponent>(entity))
        {
            for (auto child : childrenComp->m_Children)
            {
                if (m_EntityMap.count(child))
                {
                    PrintEntityHierarchy(child, indentLevel + 1);
                }
                else
                {
                    LOG_WARN("{0}  |- [INVALID CHILD] {1}", indent, (uint32_t)child);
                }
            }
        }
    }

    void lbScene::UpdateTransforms()
    {
        auto view = m_Registry.view<lbTransformComponent>();
        for (auto entity : view)
        {
            auto &transform = view.get<lbTransformComponent>(entity);
            if (transform.IsDirty())
            {
                // 强制更新世界矩阵
                transform.GetWorldMatrix();
            }
        }
    }
}