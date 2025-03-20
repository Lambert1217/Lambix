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
#include "Log/lbLog.h"
#include "lbOpenGLBuffer.h"

namespace Lambix
{
	lbOpenGLBuffer::lbOpenGLBuffer(const lbBufferSpecification &spec)
		: mBufferSpecification(spec)
	{
		glCreateBuffers(1, &mRendererID);
	}

	lbOpenGLBuffer::~lbOpenGLBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	void lbOpenGLBuffer::Bind() const
	{
		glBindBuffer(toGL(mBufferSpecification.bufferType), mRendererID);
	}

	void lbOpenGLBuffer::Unbind() const
	{
		glBindBuffer(toGL(mBufferSpecification.bufferType), 0);
	}

	void lbOpenGLBuffer::SetData(const void *data, uint32_t size)
	{
		LOG_ASSERT(size > 0, "size is not vaild");
		Bind();
		auto dataTypeSize = GetSize(mBufferSpecification.dataType);
		glBufferData(toGL(mBufferSpecification.bufferType), dataTypeSize * size, data, toGL(mBufferSpecification.bufferAllocType));
		Unbind();
	}

	void lbOpenGLBuffer::SetSubData(const void *data, const lbRange &range)
	{
		LOG_ASSERT(range.mCount > 0, "A range must be specified.");
		Bind();
		// 计算字节偏移和大小
		const GLsizeiptr dataTypeSize = GetSize(mBufferSpecification.dataType);
		const GLintptr byteOffset = range.mOffset * dataTypeSize;
		const GLsizeiptr byteSize = range.mCount * dataTypeSize;

		// 将数据指针转换为字节指针进行偏移
		const GLvoid *srcPtr = static_cast<const char *>(data) + byteOffset;

		glBufferSubData(
			toGL(mBufferSpecification.bufferType), // 缓冲类型
			byteOffset,							   // 目标缓冲区的字节偏移
			byteSize,							   // 要更新的字节数
			srcPtr								   // 数据源指针（已正确偏移）
		);
		Unbind();
	}

	uint32_t toGL(const lbBufferAllocType &value)
	{
		switch (value)
		{
		case lbBufferAllocType::StaticDrawBuffer:
			return GL_STATIC_DRAW;
		case lbBufferAllocType::DynamicDrawBuffer:
			return GL_DYNAMIC_DRAW;
		default:
			LOG_ERROR("Unknown lbBufferAllocType");
			return 0;
		}
	}

	uint32_t toGL(const lbBufferType &value)
	{
		switch (value)
		{
		case lbBufferType::ArrayBuffer:
			return GL_ARRAY_BUFFER;
		case lbBufferType::IndexBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
		default:
			LOG_ERROR("Unknown lbBufferType");
			return 0;
		}
	}
} // Lambix
