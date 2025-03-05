#include "Core/Renderer/Material/lbMaterial.h"
#include "Core/Renderer/lbRendererCommand.h"

namespace Lambix
{
    void lbMaterial::Bind()
    {
        if (m_shaderProgram)
            m_shaderProgram->Bind();

        lbRendererCommand::SetRenderState(m_renderState);

        if (!m_diffuseMap)
        {
            m_diffuseMap = lbTexture::Create(1, 1);
            uint32_t WhiteTextureData = 0xffffffff;
            m_diffuseMap->SetData(&WhiteTextureData, sizeof(uint32_t));
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