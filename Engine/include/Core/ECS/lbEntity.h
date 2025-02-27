/**
 * @file lbEntity.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 实体类
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "Core/ECS/lbScene.h"
#include "Core/Base/lbLog.h"
#include "Core/ECS/Components/lbBasicComponents.h"

namespace Lambix
{
    class lbEntity
    {
    public:
        lbEntity() = default;
        lbEntity(entt::entity handle, lbScene *scene);
        ~lbEntity() = default;

        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            LOG_ASSERT(!HasComponent<T>(), "Entity already has component!");
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template <typename T>
        T &GetComponent() const
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template <typename T>
        bool HasComponent() const
        {
            return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
        }

        template <typename T>
        void RemoveComponent()
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        void AddChild(lbEntity &child)
        {
            auto &hierarchy = GetComponent<lbHierarchyComponent>();
            hierarchy.m_Children.push_back(child);
            auto &childHierarchy = m_Scene->m_Registry.get<lbHierarchyComponent>(child);
            childHierarchy.m_Parent = m_EntityHandle;
        }

        operator bool() const { return m_EntityHandle != entt::null; }
        operator entt::entity() const { return m_EntityHandle; }
        operator uint32_t() const { return (uint32_t)m_EntityHandle; }

        const std::string &GetName() { return GetComponent<lbIdentityComponent>().m_Name; }
        const lbUUID &GetUUID() { return GetComponent<lbIdentityComponent>().m_UUID; }

    private:
        entt::entity m_EntityHandle{entt::null};
        lbScene *m_Scene = nullptr;
    };
}