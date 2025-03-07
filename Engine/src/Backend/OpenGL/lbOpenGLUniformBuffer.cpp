#include "Backend/OpenGL/lbOpenGLUniformBuffer.h"
#include "Log/lbLog.h"
#include <glad/glad.h>

namespace Lambix
{
    lbOpenGLUniformBuffer::lbOpenGLUniformBuffer(const lbUniformBufferSpec &spec)
        : m_Spec(spec)
    {
        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID,
                          m_Spec.size,
                          nullptr,
                          m_Spec.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    lbOpenGLUniformBuffer::~lbOpenGLUniformBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void lbOpenGLUniformBuffer::Bind() const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_Spec.binding, m_RendererID);
    }

    void lbOpenGLUniformBuffer::Unbind() const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_Spec.binding, 0);
    }

    void lbOpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset)
    {
        if (offset + size > m_Spec.size)
        {
            LOG_ERROR("UBO overflow! Capacity: {} Attempted write: {}+{}",
                      m_Spec.size, offset, size);
            return;
        }

        glNamedBufferSubData(m_RendererID, offset, size, data);
    }
}
