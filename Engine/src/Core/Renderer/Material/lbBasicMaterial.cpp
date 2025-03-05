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
            m_shaderProgram->UploadUniformFloat("u_Metallic", m_properties.metallic);
            m_shaderProgram->UploadUniformFloat("u_Roughness", m_properties.roughness);
        }
    }
}