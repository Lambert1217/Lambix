#include "Renderer/Material/lbPhongMaterial.h"
#include "Utils/lbFileUtils.h"
#include "Resource/lbCache.h"
#include "Resource/lbTextureLoader.h"

namespace Lambix
{
    void lbPhongMaterial::Initialize()
    {
        m_shaderProgram = lbCache::Get()->GetShaderProgram(ASSETS("Shaders/Vertex/PhongMaterial.vert"), ASSETS("Shaders/Fragment/PhongMaterial.frag"));
    }

    void lbPhongMaterial::Bind()
    {
        lbMaterial::Bind();
        // 如果没有漫反射贴图，生成一张纯白色的
        if (!m_diffuseMap)
        {
            m_diffuseMap = lbTextureLoader::CreateSolidColor(0xFFFFFFFF);
        }
    }

    void lbPhongMaterial::UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const
    {
        lbMaterial::UpdateUniforms(model, view, projection);
        if (m_shaderProgram)
        {
            // 额外
            m_shaderProgram->UploadUniformFloat4("u_BaseColor", m_properties.baseColor);
            m_shaderProgram->UploadUniformFloat("u_AmbientStrength", m_properties.ambientStrength);
            m_shaderProgram->UploadUniformFloat("u_DiffuseStrength", m_properties.diffuseStrength);
            m_shaderProgram->UploadUniformFloat("u_SpecularStrength", m_properties.specularStrength);
            m_shaderProgram->UploadUniformInt("u_Shininess", m_properties.shininess);
        }
    }
}