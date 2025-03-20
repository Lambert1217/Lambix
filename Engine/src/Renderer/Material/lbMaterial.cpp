#include "Renderer/Material/lbMaterial.h"
#include "Renderer/lbRendererCommand.h"
#include "Resource/lbTextureLoader.h"
#include "lbMaterial.h"

namespace Lambix
{
    void lbMaterial::Bind()
    {
        if (m_shaderProgram)
        {
            m_shaderProgram->Bind();
            m_shaderProgram->BindUniformBlock("LightingUBO", 1);
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
    }
}
