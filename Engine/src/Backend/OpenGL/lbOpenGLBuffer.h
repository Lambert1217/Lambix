/**
 ***************************************************************
 * @file            : lbOpenGLBuffer.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Renderer/Interfaces/lbBuffer.h"
#include "glad/glad.h"

namespace Lambix
{
	class lbOpenGLBuffer : public lbBuffer
	{
	public:
		lbOpenGLBuffer(const lbBufferSpecification &spec);
		~lbOpenGLBuffer() override;

		void Bind() const override;

		void Unbind() const override;

		void SetSubData(const void *data, const lbRange &range = {}) override;
		void SetData(const void *data, uint32_t size) override;

	private:
		GLuint mRendererID;
		lbBufferSpecification mBufferSpecification;
	};

	static uint32_t toGL(const lbBufferAllocType &value);
	static uint32_t toGL(const lbBufferType &value);
} // Lambix
