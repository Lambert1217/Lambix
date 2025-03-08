/**
 * @file lbLightSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 光源系统
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "lbSystem.h"
#include "Renderer/lbUniformBuffer.h"
#include "ECS/Components/lbLightComponent.h"

namespace Lambix
{
    class lbLightSystem : public lbSystem
    {
    public:
        explicit lbLightSystem(lbScene *scene);

        void Init() override;
        void OnUpdate(lbTimestep ts) override;

    private:
        friend class lbLightComponent;
        lbLightsData m_LightsData;
        std::shared_ptr<lbUniformBuffer> m_LightingUBO;
    };
}