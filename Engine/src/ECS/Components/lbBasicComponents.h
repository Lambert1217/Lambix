/**
 * @file lbBasicComponents.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 基础组件
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "lbComponent.h"
#include "lbTransformComponent.h"
#include "Utils/lbUUID.h"

namespace Lambix
{
    struct lbIdentityComponent : public lbComponent
    {
        lbUUID m_UUID;      // 实体唯一标识
        std::string m_Name; // 实体名称

        lbIdentityComponent() : m_UUID(GenUUID()), m_Name(std::string()) {}
        lbIdentityComponent(lbUUID uuid, const std::string &name) : m_UUID(uuid), m_Name(name) {}
    };

    struct lbTagComponent : public lbComponent
    {
        std::vector<std::string> m_Tags; // 标签列表
    };

    struct lbParentComponent : public lbComponent
    {
        entt::entity m_Parent{entt::null};
    };

    struct lbChildrenComponent : public lbComponent
    {
        std::vector<entt::entity> m_Children;
    };

    struct lbFlagComponent : public lbComponent
    {
        uint32_t m_Flags{0}; // 标志位
        // 第一位表示是否可渲染
        static constexpr uint32_t RENDERABLE = 1 << 0;
        void SetRenderable(bool renderable)
        {
            if (renderable)
                m_Flags |= RENDERABLE;
            else
                m_Flags &= ~RENDERABLE;
        }
        bool IsRenderable() const { return m_Flags & RENDERABLE; }
    };
}