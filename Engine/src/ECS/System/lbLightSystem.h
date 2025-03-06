/**
 * @file lbLightSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "ECS/lbScene.h"
#include "Renderer/lbUniformBuffer.h"
#include "Renderer/Light/lbLightingDefines.h"
#include "ECS/Components/lbLightComponent.h"

namespace Lambix
{
    class lbLightSystem
    {
    public:
        explicit lbLightSystem(lbScene *scene);

        void Init();
        void OnUpdate(lbTimestep ts);

    private:
        void CollectLightData();

        lbScene *m_Scene;
        lbLightData m_LightData;
        std::shared_ptr<lbUniformBuffer> m_LightingUBO;
    };
}