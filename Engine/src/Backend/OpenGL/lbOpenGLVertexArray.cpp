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
#include "lbOpenGLVertexArray.h"
#include "Log/lbLog.h"
#include "Core/lbCore.h"

namespace Lambix
{
	lbOpenGLVertexArray::lbOpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	lbOpenGLVertexArray::~lbOpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void lbOpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void lbOpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void lbOpenGLVertexArray::lbVertexAttribPointer(uint32_t binding, uint32_t itemSize, const lbDataType &type, bool normalized, uint32_t stride, const void *pointer)
	{
		glEnableVertexAttribArray(binding);
		glVertexAttribPointer(binding, itemSize, toGL(type), normalized, stride, pointer);
	}

	GLenum toGL(const lbDataType &type)
	{
		switch (type)
		{
		case lbDataType::UnsignedByteType:
			return GL_UNSIGNED_BYTE;
		case lbDataType::FloatType:
			return GL_FLOAT;
		case lbDataType::ByteType:
			return GL_BYTE;
		case lbDataType::Int32Type:
			return GL_INT;
		case lbDataType::UInt32Type:
			return GL_UNSIGNED_INT;
		default:
			LOG_ERROR("Unknown lbDataType");
			return 0;
		}
	}
} // Lambix