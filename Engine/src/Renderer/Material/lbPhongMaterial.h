/**
 * @brief Phong光照材质实现
 *
 */

#pragma once
#include "Renderer/Material/lbMaterial.h"

namespace Lambix
{
    class lbPhongMaterial : public lbMaterial
    {
    public:
        using Ptr = std::shared_ptr<lbPhongMaterial>;
        static Ptr Create()
        {
            auto mat = std::make_shared<lbPhongMaterial>();
            mat->Initialize();
            return mat;
        }

        void Bind() override;

        void UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const override;
        lbMaterialType GetMaterialType() const override { return lbMaterialType::Phong; }

        // 基础材质属性
        struct Properties
        {
            glm::vec4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
            float ambientStrength = 0.2;
            float diffuseStrength = 0.7;
            float specularStrength = 0.4;
            int shininess = 32;
        };

        Properties &GetProperties() { return m_properties; }

    private:
        void Initialize();

        Properties m_properties;
    };
}
