#include "lbCubeMaterial.h"
#include "Utils/lbFileUtils.h"
#include "Resource/lbCache.h"

namespace Lambix
{
    void lbCubeMaterial::Initialize()
    {
        m_shaderProgram = lbCache::Get()->GetShaderProgram(ASSETS("Shaders/Vertex/CubeMaterial.vert"), ASSETS("Shaders/Fragment/CubeMaterial.frag"));
        m_renderState.depthFunc = DepthFunc::LessEqual;
    }

    void lbCubeMaterial::UpdateUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const
    {
        lbMaterial::UpdateUniforms(model, view, projection);
        if (m_shaderProgram)
        {
            // 额外
            if (m_properties.mCubeMap)
            {
                m_properties.mCubeMap->Bind(0);
                m_shaderProgram->UploadUniformInt("u_CubeMap", 0);
            }
        }
    }
} // namespace Lambix
