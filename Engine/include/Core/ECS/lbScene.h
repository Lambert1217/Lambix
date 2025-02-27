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

namespace Lambix
{
    class lbEntity;
    class lbScene
    {
    public:
        lbScene() = default;
        ~lbScene() = default;

        lbEntity CreateEntity(const std::string &name);
        lbEntity CreateEntityWithUUID(const std::string &name, lbUUID uuid);

        void OnUpdate();

    private:
        friend class lbEntity;

        entt::registry m_Registry;
        std::unordered_map<entt::entity, lbEntity> m_EntityMap;
    };
}
