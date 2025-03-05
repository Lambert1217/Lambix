#include "Core/Renderer/Material/lbMaterial.h"
#include "Core/Renderer/lbRendererCommand.h"
#include "Core/Resource/lbResourceManager.h"

namespace Lambix
{
    void lbMaterial::Bind()
    {
        if (m_shaderProgram)
            m_shaderProgram->Bind();

        lbRendererCommand::SetRenderState(m_renderState);

        if (!m_diffuseMap)
        {
            m_diffuseMap = lbResourceManager::GetInstance().PureWhite1_1;
        }

        m_diffuseMap->Bind(0);
        m_shaderProgram->UploadUniformInt("u_DiffuseMap", 0);
    }

    void lbMaterial::Unbind()
    {
        if (m_shaderProgram)
            m_shaderProgram->Unbind();
    }
}