/**
 * @file lbTransformSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 变换系统
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbSystem.h"

namespace Lambix
{
    class lbTransformSystem : public lbSystem
    {
    public:
        explicit lbTransformSystem(lbScene *scene);

        void OnUpdate(lbTimestep ts) override;
    };
} // namespace Lambix
