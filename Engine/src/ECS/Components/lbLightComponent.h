/**
 * @file lbLightComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 光照组件
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <glm/glm.hpp>
#include "ECS/Components/lbComponent.h"
#include "Renderer/Light/lbLight.h"

namespace Lambix
{
    class lbLightComponent : public lbComponent
    {
    public:
        lbLightComponent() = default;
        ~lbLightComponent() = default;

        // 类型安全的动态转换
        template <typename T>
        std::shared_ptr<T> As() const
        {
            if (m_Light && m_Light->GetLightType() == T::GetStaticType())
            {
                return std::static_pointer_cast<T>(m_Light);
            }
            return nullptr;
        }

        template <typename T, typename... Args>
        void Create(Args &&...args)
        {
            m_Light = std::make_shared<T>(std::forward<Args>(args)...);
        }

        // 判断当前类型
        lbLightType GetType() const;

        void OnUpdate(lbTimestep ts) override;

    private:
        void ProcessDirectional();
        void ProcessPoint();
        void ProcessSpot();

    private:
        std::shared_ptr<lbLight> m_Light{nullptr};
    };
}
