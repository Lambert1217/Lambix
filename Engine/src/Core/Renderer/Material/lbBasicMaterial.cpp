#include "Core/Renderer/Material/lbBasicMaterial.h"
#include "Core/Utils/lbFileUtils.h"
#include "Core/Resource/lbResourceManager.h"

namespace Lambix
{
    void lbBasicMaterial::Initialize()
    {
        std::string vertexShaderPath = lbJoinPath(lbResRootDir, "Shaders/Vertex/BasicMaterial.vert");
        std::string fragmentShaderPath = lbJoinPath(lbResRootDir, "Shaders/Fragment/BasicMaterial.frag");
        m_shaderProgram = lbResourceManager::GetInstance().GetShaderProgram(vertexShaderPath, fragmentShaderPath);
    }

    void lbBasicMaterial::UpdateUniforms() const
    {
        if (m_shaderProgram)
        {
            m_shaderProgram->UploadUniformFloat4("u_BaseColor", m_properties.baseColor);

            // 上传PBR参数
            m_shaderProgram->UploadUniformFloat3("u_PBR.albedo", m_properties.albedo);
            m_shaderProgram->UploadUniformFloat("u_PBR.Metallic", m_properties.metallic);
            m_shaderProgram->UploadUniformFloat("u_PBR.Roughness", m_properties.roughness);
            m_shaderProgram->UploadUniformFloat("u_PBR.ao", m_properties.ao);
        }
    }
}