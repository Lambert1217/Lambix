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

#include "Core/Base/lbUUID.h"
#include "entt/entt.hpp"
#include "Core/Base/lbTimestep.h"

namespace Lambix
{
    class lbEntity;
    class lbScene
    {
    public:
        lbScene() = default;
        ~lbScene() = default;

        std::shared_ptr<lbEntity> CreateEntity(const std::string &name);
        std::shared_ptr<lbEntity> CreateEntityWithUUID(const std::string &name, lbUUID uuid);

        void DestroyEntity(std::shared_ptr<lbEntity> entity);

        void OnUpdate(lbTimestep ts);

    private:
        void PrintEntityHierarchy(entt::entity entity, int indentLevel);

    private:
        friend class lbEntity;

        entt::registry m_Registry;
        std::unordered_map<entt::entity, std::shared_ptr<lbEntity>> m_EntityMap;
    };
}
