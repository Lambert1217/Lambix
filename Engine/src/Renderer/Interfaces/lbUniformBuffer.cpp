#include "lbUniformBuffer.h"
#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLUniformBuffer.h"
#endif

namespace Lambix
{
    std::shared_ptr<lbUniformBuffer> lbUniformBuffer::Create(const lbUniformBufferSpec &spec)
    {
#ifdef LAMBIX_USE_OPENGL
        return std::make_shared<lbOpenGLUniformBuffer>(spec);
#endif
    }
}
