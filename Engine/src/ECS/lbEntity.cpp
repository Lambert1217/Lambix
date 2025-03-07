#include "lbEntity.h"
#include "ECS/Components/lbTransformComponent.h"

namespace Lambix
{
    lbEntity::lbEntity(entt::entity handle, lbScene *scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }

    void lbEntity::SetParent(std::shared_ptr<lbEntity> parent)
    {
        // 如果parent为空，或者parent的不是同一个场景
        if (!parent || parent->m_Scene != m_Scene)
        {
            LOG_ERROR("Invalid parent entity or scene mismatch");
            return;
        }

        // 获取或创建当前实体的Parent组件
        auto &parentComp = m_Scene->GetRegistry().get_or_emplace<lbParentComponent>(m_EntityHandle);

        // 如果已经是其父实体，直接返回
        if (parentComp.m_Parent == parent->m_EntityHandle)
        {
            LOG_WARN("Entity {} is already the parent entity of Entity {}.", parent->GetName(), GetName());
            return;
        }

        // 处理旧父节点：如果原先有父节点，先从其父实体的子实体列表删除
        if (parentComp.m_Parent != entt::null)
        {
            if (auto oldParent = m_Scene->GetEntity(parentComp.m_Parent); oldParent)
            {
                auto &oldChildren = oldParent->GetComponent<lbChildrenComponent>();
                oldChildren.m_Children.erase(
                    std::remove(oldChildren.m_Children.begin(),
                                oldChildren.m_Children.end(),
                                m_EntityHandle),
                    oldChildren.m_Children.end());
            }
        }

        // 设置新父节点
        parentComp.m_Parent = parent->m_EntityHandle;

        // 更新新父节点的Children组件
        auto &newChildren = m_Scene->GetRegistry().get_or_emplace<lbChildrenComponent>(parent->m_EntityHandle);
        if (std::find(newChildren.m_Children.begin(),
                      newChildren.m_Children.end(),
                      m_EntityHandle) == newChildren.m_Children.end())
        {
            newChildren.m_Children.push_back(m_EntityHandle);
        }

        // 更新变换组件父子关系
        GetComponent<lbTransformComponent>().m_Transform.SetDirty();
    }

    std::shared_ptr<lbEntity> lbEntity::GetParent() const
    {
        if (!HasParent())
        {
            return nullptr;
        }
        if (auto it = m_Scene->GetEntity(GetComponent<lbParentComponent>().m_Parent); it)
        {
            // 找到父实体
            return it;
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<lbEntity>> lbEntity::GetChildren() const
    {
        std::vector<std::shared_ptr<lbEntity>> children;
        if (auto *childrenComp = m_Scene->GetRegistry().try_get<lbChildrenComponent>(m_EntityHandle))
        {
            for (auto childHandle : childrenComp->m_Children)
            {
                if (auto it = m_Scene->GetEntity(childHandle); it)
                {
                    children.push_back(it);
                }
            }
        }
        return children;
    }
}