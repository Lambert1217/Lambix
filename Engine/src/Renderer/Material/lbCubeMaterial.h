/**
 * @file lbCubeMaterial.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 立方体材质 可以用于天空盒
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbMaterial.h"

namespace Lambix
{
    class lbCubeMaterial : public lbMaterial
    {
    public:
        using Ptr = std::shared_ptr<lbCubeMaterial>;
        static Ptr Create()
        {
            auto mat = std::make_shared<lbCubeMaterial>();
            mat->Initialize();
            return mat;
        }

        void UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const override;
        lbMaterialType GetMaterialType() const override { return lbMaterialType::Basic; }

        // 基础材质属性
        struct Properties
        {
        };

        Properties &GetProperties() { return m_properties; }

    private:
        void Initialize();

        Properties m_properties;
    };
} // namespace Lambix
