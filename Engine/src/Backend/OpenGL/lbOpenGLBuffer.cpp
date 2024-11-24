/**
 ***************************************************************
 * @file            : lbOpenGLBuffer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLBuffer.h"
#include "Core/Base/lbLog.h"
#include "glad/glad.h"

namespace Lambix
{
    // lbOpenGLVertexBuffer
	lbOpenGLVertexBuffer::lbOpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	lbOpenGLVertexBuffer::~lbOpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void lbOpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void lbOpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// lbOpenGLIndexBuffer
	lbOpenGLIndexBuffer::lbOpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	lbOpenGLIndexBuffer::~lbOpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void lbOpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void lbOpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} // Lambix