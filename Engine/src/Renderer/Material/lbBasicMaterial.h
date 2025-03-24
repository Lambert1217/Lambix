/**
 * @brief 基础材质实现
 *
 */

#pragma once
#include "Renderer/Material/lbMaterial.h"

namespace Lambix
{
    class lbBasicMaterial : public lbMaterial
    {
    public:
        using Ptr = std::shared_ptr<lbBasicMaterial>;
        static Ptr Create()
        {
            auto mat = std::make_shared<lbBasicMaterial>();
            mat->Initialize();
            return mat;
        }

        void Bind() override;

        void UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const override;
        lbMaterialType GetMaterialType() const override { return lbMaterialType::Basic; }

        // 基础材质属性
        struct Properties
        {
            glm::vec4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
                };

        Properties &GetProperties() { return m_properties; }

    private:
        void Initialize();

        Properties m_properties;
    };
}
