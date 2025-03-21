#include "Renderer/Material/lbMaterial.h"
#include "Renderer/lbRendererCommand.h"
#include "Resource/lbTextureLoader.h"
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

        // 如果没有漫反射贴图，生成一张纯白色的
        if (!m_diffuseMap)
        {
            m_diffuseMap = lbTextureLoader::CreateSolidColor(0xFFFFFFFF);
        }
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
        // 光照UBO
        m_shaderProgram->BindUniformBlock("LightingUBO", 1);
    }
}
