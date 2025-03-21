/**
 * @file lbMesh.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 由几何信息（geometry）和材质（material）组成
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbGeometry.h"
#include "Material/lbMaterial.h"

namespace Lambix
{
    struct lbMesh
    {
        std::string name; // 添加名称标识
        lbGeometry::Ptr mGeometry{nullptr};
        lbMaterial::Ptr mMaterial{nullptr};

        using Ptr = std::shared_ptr<lbMesh>;
        static Ptr Create()
        {
            return std::make_shared<lbMesh>();
        }
    };
} // namespace Lambix
