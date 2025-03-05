#include "Core/Renderer/Material/lbBasicMaterial.h"
#include "Core/Utils/lbFileUtils.h"

namespace Lambix
{
    void lbBasicMaterial::Initialize()
    {
        auto vertexShader = lbShader::Create(lbShaderType::Vertex);
        vertexShader->CompileFromFile(lbJoinPath(lbResRootDir, "Shaders/Vertex/BasicMaterial.vert"));
        auto fragShader = lbShader::Create(lbShaderType::Fragment);
        fragShader->CompileFromFile(lbJoinPath(lbResRootDir, "Shaders/Fragment/BasicMaterial.frag"));

        m_shaderProgram = lbShaderProgram::Create();
        m_shaderProgram->Link(vertexShader, fragShader);
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