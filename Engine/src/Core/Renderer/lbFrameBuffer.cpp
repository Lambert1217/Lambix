#include "Core/Renderer/lbFrameBuffer.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLFrameBuffer.h"
#endif

namespace Lambix
{

    std::shared_ptr<lbFrameBuffer> Lambix::lbFrameBuffer::Create(const lbFrameBufferSpecification &spec)
    {
#ifdef LAMBIX_USE_OPENGL
        return std::make_shared<lbOpenGLFrameBuffer>(spec);
#endif
    }

}
