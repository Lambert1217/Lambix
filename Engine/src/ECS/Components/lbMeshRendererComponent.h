/**
 * @file lbMeshRendererComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 渲染组件
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "Renderer/Geometry/lbGeometry.h"
#include "Renderer/Material/lbMaterial.h"
#include "ECS/Components/lbComponent.h"

namespace Lambix
{
    struct lbMeshRendererComponent : public lbComponent
    {
        lbGeometry::Ptr geometry;
        lbMaterial::Ptr material;

        void OnUpdate(lbTimestep ts) override;
    };
} // namespace Lambix
