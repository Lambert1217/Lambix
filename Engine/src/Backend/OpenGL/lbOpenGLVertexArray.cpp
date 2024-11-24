/**
 ***************************************************************
 * @file            : lbOpenGLVertexArray.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLVertexArray.h"
#include "glad/glad.h"
#include "Core/Base/lbLog.h"

namespace Lambix
{
	static GLenum ShaderDataTypeToOpenGLBaseType(lbShaderDataType type)
	{
		switch (type)
		{
		case lbShaderDataType::Float:
			return GL_FLOAT;
		case lbShaderDataType::Float2:
			return GL_FLOAT;
		case lbShaderDataType::Float3:
			return GL_FLOAT;
		case lbShaderDataType::Float4:
			return GL_FLOAT;
		case lbShaderDataType::Mat3:
			return GL_FLOAT;
		case lbShaderDataType::Mat4:
			return GL_FLOAT;
		case lbShaderDataType::Int:
			return GL_INT;
		case lbShaderDataType::Int2:
			return GL_INT;
		case lbShaderDataType::Int3:
			return GL_INT;
		case lbShaderDataType::Int4:
			return GL_INT;
		case lbShaderDataType::Bool:
			return GL_BOOL;
		}

		LOG_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	lbOpenGLVertexArray::lbOpenGLVertexArray() : index(0)
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	lbOpenGLVertexArray::~lbOpenGLVertexArray()
	{
	}
	void lbOpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void lbOpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void lbOpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<lbVertexBuffer> vertexBuffer)
	{
		LOG_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto &layout = vertexBuffer->GetLayout();
		for (const auto &element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void *)(intptr_t)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	void lbOpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<lbIndexBuffer> indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
} // Lambix