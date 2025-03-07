/**
 * @file lbTransformComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 变换组件
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "Core/lbTransform.h"
#include "ECS/Components/lbComponent.h"

namespace Lambix
{
    class lbTransformComponent : public lbComponent
    {
    public:
        lbTransformComponent();

        void OnUpdate(lbTimestep ts) override;

    public:
        lbTransform m_Transform;

    private:
        // 遍历所有孩子，也设置为脏
        void SetDirty();
    };
}
