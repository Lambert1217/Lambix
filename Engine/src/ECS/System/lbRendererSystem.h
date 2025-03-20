/**
 * @file lbRendererSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 渲染系统  优先级为4
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbSystem.h"
#include "Renderer/Driver/lbDriverAttribute.h"
#include "Renderer/Driver/lbDriverGeometry.h"
#include "Renderer/Driver/lbDriverInfo.h"

namespace Lambix
{
    class lbRendererSystem : public lbSystem
    {
    public:
        explicit lbRendererSystem(lbScene *scene);

        void Init() override;
        void OnUpdate(lbTimestep ts) override;

    private:
        friend class lbMeshRendererComponent;
        lbDriverAttributes::Ptr mAttributes;
        lbDriverBindingStates::Ptr mBindingStates;
        lbDriverInfo::Ptr mInfo;
        lbDriverGeometries::Ptr mGeometries;
    };
} // namespace Lambix
