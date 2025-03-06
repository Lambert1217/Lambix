/**
 * @brief Phong材质实现
 *
 */

#pragma once
#include "Core/Renderer/Material/lbMaterial.h"

namespace Lambix
{
    // Phong材质实现
    class lbPhongMaterial : public lbMaterial
    {
    public:
        static Ptr Create()
        {
            auto mat = std::make_shared<lbPhongMaterial>();
            mat->Initialize();
            return mat;
        }

        void UpdateUniforms() const override;
        std::string GetMaterialType() const override { return "Phong"; }

        // Phong材质属性
        struct PhongProperties
        {
            glm::vec4 diffuseColor = glm::vec4(1.0f);
            glm::vec4 specularColor = glm::vec4(1.0f);
            float shininess = 32.0f;
        };

        PhongProperties &GetPhongProperties() { return m_phongProps; }

    private:
        void Initialize();

        PhongProperties m_phongProps;
    };
}