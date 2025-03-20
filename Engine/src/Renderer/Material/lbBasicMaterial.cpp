#include "Renderer/Material/lbBasicMaterial.h"
#include "Utils/lbFileUtils.h"
#include "Resource/lbCache.h"

namespace Lambix
{
    void lbBasicMaterial::Initialize()
    {
        m_shaderProgram = lbCache::Get()->GetShaderProgram(ASSETS("Shaders/Vertex/BasicMaterial.vert"), ASSETS("Shaders/Fragment/BasicMaterial.frag"));
    }

    void lbBasicMaterial::UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const
    {
        lbMaterial::UpdateUniforms(model, view, projection);
        if (m_shaderProgram)
        {
            // 额外
            m_shaderProgram->UploadUniformFloat4("u_BaseColor", m_properties.baseColor);
        }
    }
}