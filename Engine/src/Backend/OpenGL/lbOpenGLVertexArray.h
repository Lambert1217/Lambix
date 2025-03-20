/**
 ***************************************************************
 * @file            : lbOpenGLVertexArray.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Renderer/Interfaces/lbVertexArray.h"
#include "glad/glad.h"

namespace Lambix
{

	class lbOpenGLVertexArray : public lbVertexArray
	{
	public:
		lbOpenGLVertexArray();
		~lbOpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void lbVertexAttribPointer(uint32_t binding, uint32_t itemSize, const lbDataType &type, bool normalized, uint32_t stride, const void *pointer) override;

	private:
		uint32_t m_RendererID;
	};

	static GLenum toGL(const lbDataType &type);

} // Lambix
