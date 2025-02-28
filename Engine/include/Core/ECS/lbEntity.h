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
            return m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template <typename T>
        T &GetComponent() const
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            return m_Scene->GetRegistry().get<T>(m_EntityHandle);
        }

        template <typename T>
        bool HasComponent() const
        {
            return m_Scene->GetRegistry().any_of<T>(m_EntityHandle);
        }

        template <typename T>
        void RemoveComponent()
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            m_Scene->GetRegistry().remove<T>(m_EntityHandle);
        }

        void SetParent(std::shared_ptr<lbEntity> parent);
        std::vector<std::shared_ptr<lbEntity>> GetChildren() const;

        bool IsValid() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }
        operator bool() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }
        operator entt::entity() const { return m_EntityHandle; }
        operator uint32_t() const { return (uint32_t)m_EntityHandle; }

        const std::string &GetName() { return GetComponent<lbIdentityComponent>().m_Name; }
        const lbUUID &GetUUID() { return GetComponent<lbIdentityComponent>().m_UUID; }
        lbScene *GetScene() const { return m_Scene; }

    private:
        entt::entity m_EntityHandle{entt::null};
        lbScene *m_Scene = nullptr;
    };
}