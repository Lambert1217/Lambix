#include "Renderer/Material/lbMaterial.h"
#include "Renderer/lbRendererCommand.h"
#include "Resource/lbResourceManager.h"

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

        if (!m_diffuseMap)
        {
            m_diffuseMap = lbResourceManager::GetInstance().PureWhite1_1;
        }

        m_diffuseMap->Bind(0);
        m_shaderProgram->UploadUniformInt("u_DiffuseMap", 0);

        if (m_normalMap)
        {
            m_normalMap->Bind(1);
            m_shaderProgram->UploadUniformInt("u_NormalMap", 1);
        }
    }

    void lbMaterial::Unbind()
    {
        if (m_shaderProgram)
            m_shaderProgram->Unbind();
    }
}