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
    }
} // namespace Lambix
