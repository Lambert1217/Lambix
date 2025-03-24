#include "Renderer/Material/lbMaterial.h"
#include "Renderer/lbRendererCommand.h"
#include "lbMaterial.h"
#include "Events/lbEventPool.h"

namespace Lambix
{
    lbMaterial::~lbMaterial()
    {
        // ShaderProgramRelease event
        if (m_shaderProgram)
        {
            auto event = lbEventPool::Get()->Acquire();
            event->Set("ShaderProgramRelease", this, m_shaderProgram.get());
            lbEventDispatcher::Get()->dispatchEvent(event);
        }
    }

    void lbMaterial::Bind()
    {
        if (m_shaderProgram)
        {
            m_shaderProgram->Bind();
        }

        lbRendererCommand::SetRenderState(m_renderState);
    }

    void lbMaterial::Unbind()
    {
        if (m_shaderProgram)
            m_shaderProgram->Unbind();
    }
}

void Lambix::lbMaterial::UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const
{
    if (m_shaderProgram)
    {
        // MVP
        m_shaderProgram->UploadUniformMat4("u_Model", model);
        m_shaderProgram->UploadUniformMat4("u_View", view);
        m_shaderProgram->UploadUniformMat4("u_Projection", projection);
        // DiffuseMap
        if (m_diffuseMap)
        {
            m_diffuseMap->Bind(0);
            m_shaderProgram->UploadUniformInt("u_DiffuseMap", 0);
        }
        if (m_normalMap)
        {
            m_normalMap->Bind(1);
            m_shaderProgram->UploadUniformInt("u_NormalMap", 1);
        }
        if (m_specularMap)
        {
            m_specularMap->Bind(2);
            m_shaderProgram->UploadUniformInt("u_SpecularMap", 2);
        }
        if (m_CubeMap)
        {
            m_CubeMap->Bind(3);
            m_shaderProgram->UploadUniformInt("u_CubeMap", 3);
        }
        // 光照UBO
        m_shaderProgram->BindUniformBlock("u_LightingUBO", 1);
    }
}
