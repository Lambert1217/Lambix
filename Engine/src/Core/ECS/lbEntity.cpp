#include "Core/ECS/lbEntity.h"

namespace Lambix
{
    lbEntity::lbEntity(entt::entity handle, lbScene *scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {
    }

    void lbEntity::SetParent(std::shared_ptr<lbEntity> parent)
    {
        if (!parent || !parent->IsValid() || !IsValid() || parent->m_Scene != m_Scene)
        {
            LOG_ERROR("Invalid parent entity or scene mismatch");
            return;
        }

        // 获取或创建当前实体的Parent组件
        auto &parentComp = m_Scene->m_Registry.get_or_emplace<lbParentComponent>(m_EntityHandle);

        // 处理旧父节点
        if (parentComp.m_Parent != entt::null)
        {
            if (auto oldParent = m_Scene->m_EntityMap.find(parentComp.m_Parent);
                oldParent != m_Scene->m_EntityMap.end())
            {
                auto &oldChildren = oldParent->second->GetComponent<lbChildrenComponent>();
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
        auto &newChildren = parent->m_Scene->m_Registry.get_or_emplace<lbChildrenComponent>(parent->m_EntityHandle);
        if (std::find(newChildren.m_Children.begin(),
                      newChildren.m_Children.end(),
                      m_EntityHandle) == newChildren.m_Children.end())
        {
            newChildren.m_Children.push_back(m_EntityHandle);
        }
    }

    std::vector<std::shared_ptr<lbEntity>> lbEntity::GetChildren() const
    {
        std::vector<std::shared_ptr<lbEntity>> children;
        if (auto *childrenComp = m_Scene->m_Registry.try_get<lbChildrenComponent>(m_EntityHandle))
        {
            for (auto childHandle : childrenComp->m_Children)
            {
                if (auto it = m_Scene->m_EntityMap.find(childHandle);
                    it != m_Scene->m_EntityMap.end())
                {
                    children.push_back(it->second);
                }
            }
        }
        return children;
    }
}