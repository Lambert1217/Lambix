/**
 * @brief 基础材质实现
 *
 */

#pragma once
#include "Core/Renderer/Material/lbMaterial.h"

namespace Lambix
{
    class lbBasicMaterial : public lbMaterial
    {
    public:
        static Ptr Create()
        {
            auto mat = std::make_shared<lbBasicMaterial>();
            mat->Initialize();
            return mat;
        }

        void UpdateUniforms() const override;
        std::string GetMaterialType() const override { return "Basic"; }

        // 基础材质属性
        struct Properties
        {
            glm::vec4 baseColor = glm::vec4(1.0f);
            float metallic = 0.0f;
            float roughness = 0.5f;
        };

        Properties &GetProperties() { return m_properties; }

    private:
        void Initialize();

        Properties m_properties;
    };
}
