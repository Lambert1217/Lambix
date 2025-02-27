#include "Core/ECS/lbScene.h"
#include "Core/ECS/lbEntity.h"
#include "Core/ECS/Components/lbBasicComponents.h"

namespace Lambix
{
    lbEntity lbScene::CreateEntity(const std::string &name)
    {
        return CreateEntityWithUUID(name, GenUUID());
    }

    lbEntity lbScene::CreateEntityWithUUID(const std::string &name, lbUUID uuid)
    {
        lbEntity entity = {m_Registry.create(), this};
        entity.AddComponent<lbIdentityComponent>(uuid, name);
        entity.AddComponent<lbHierarchyComponent>();

        m_EntityMap[entity] = entity;
        return entity;
    }

    void lbScene::OnUpdate()
    {
        // 输出实体父子关系
        std::queue<lbEntity> entityQueue;
        auto &view = m_Registry.view<lbHierarchyComponent>();

        for (auto entity : view)
        {
            auto &hierarchy = view.get<lbHierarchyComponent>(entity);
            if (hierarchy.m_Parent == entt::null)
            {
                LOG_INFO("Entity: {0}, Parent: null", m_EntityMap[entity].GetName());
            }
            for (auto child : hierarchy.m_Children)
            {
                entityQueue.push(m_EntityMap[child]);
            }
        }
        while (!entityQueue.empty())
        {
            auto entity = entityQueue.front();
            entityQueue.pop();
            auto &hierarchy = entity.GetComponent<lbHierarchyComponent>();
            LOG_INFO("Entity: {0}, Parent: {1}", entity.GetName(), m_EntityMap[hierarchy.m_Parent].GetName());
            for (auto child : hierarchy.m_Children)
            {
                entityQueue.push(m_EntityMap[child]);
            }
        }
    }
}