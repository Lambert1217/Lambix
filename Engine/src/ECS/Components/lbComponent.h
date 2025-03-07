/**
 * @file lbComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 组件基类
 * @date 2025-03-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Utils/lbTimestep.h"
#include "Events/Event.h"
#include "Log/lbLog.h"

namespace Lambix
{
    class lbEntity;
    class lbScene;

    struct lbComponent
    {
        lbComponent() = default;
        virtual ~lbComponent() = default;

        virtual void OnUpdate(lbTimestep ts) {}
        virtual void OnEvent(Event &e) {}

        virtual void SetOwner(const std::shared_ptr<lbEntity> &entity)
        {
            LOG_ASSERT(entity, "The entity is empty.");
            m_Entity = entity;
        }

        /* data */
        std::weak_ptr<lbEntity> m_Entity;
        };

}