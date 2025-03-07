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
#include "ECS/lbScene.h"
#include "Log/lbLog.h"
#include "ECS/Components/lbBasicComponents.h"

namespace Lambix
{
    class lbEntity : public std::enable_shared_from_this<lbEntity>
    {
    public:
        lbEntity() = default;
        lbEntity(entt::entity handle, lbScene *scene);
        ~lbEntity() = default;

        // 添加组件
        template <typename T, typename... Args>
        T &AddComponent(Args &&...args)
        {
            LOG_ASSERT(!HasComponent<T>(), "Entity already has component!");
            auto &comp = m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            comp.SetOwner(shared_from_this());
            return comp;
        }

        // 获取组件的引用
        template <typename T>
        T &GetComponent() const
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            return m_Scene->GetRegistry().get<T>(m_EntityHandle);
        }

        // 是否包含某种组件
        template <typename T>
        bool HasComponent() const
        {
            return m_Scene->GetRegistry().any_of<T>(m_EntityHandle);
        }

        // 移除组件
        template <typename T>
        void RemoveComponent()
        {
            LOG_ASSERT(HasComponent<T>(), "Entity does not have component!");
            m_Scene->GetRegistry().remove<T>(m_EntityHandle);
        }

        // 设置父实体
        void SetParent(std::shared_ptr<lbEntity> parent);

        // 获取父实体，若没有返回空
        std::shared_ptr<lbEntity> GetParent() const;

        // 是否有父实体
        bool HasParent() const { return GetComponent<lbParentComponent>().m_Parent != entt::null; }

        // 获取子实体列表
        std::vector<std::shared_ptr<lbEntity>> GetChildren() const;

        const std::string &GetName() { return GetComponent<lbIdentityComponent>().m_Name; }

        const lbUUID &GetUUID() { return GetComponent<lbIdentityComponent>().m_UUID; }

        lbScene *GetScene() const { return m_Scene; }

        // 获取entt::entity
        entt::entity GetHandle() const { return m_EntityHandle; }

        uint32_t ToUint32() const { return static_cast<uint32_t>(m_EntityHandle); }

    private:
        entt::entity m_EntityHandle{entt::null};
        lbScene *m_Scene = nullptr;
    };
}