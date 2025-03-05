/**
 * @file lbCubeGeometry.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief cube
 * @date 2025-03-05
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "Core/Renderer/Geometry/lbGeometry.h"

namespace Lambix
{
    class lbCubeGeometry : public lbGeometry
    {
    public:
        using Ptr = std::shared_ptr<lbCubeGeometry>;
        static Ptr Create(float size = 1.0f);

        explicit lbCubeGeometry(float size = 1.0f);

    private:
        void GenerateVertexData(float size);
    };
}