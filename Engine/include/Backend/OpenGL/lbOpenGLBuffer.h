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

#include "Core/Renderer/lbBuffer.h"

namespace Lambix
{

	class lbOpenGLVertexBuffer : public lbVertexBuffer
	{
	 public:
		lbOpenGLVertexBuffer(float *vertices, uint32_t size);
		~lbOpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		void SetLayout(const lbBufferLayout& layout) override {m_Layout = layout;}
		[[nodiscard]] const lbBufferLayout& GetLayout() const override {return m_Layout;}
	 private:
		uint32_t m_RendererID;
		lbBufferLayout m_Layout;
	};

	class lbOpenGLIndexBuffer : public lbIndexBuffer
	{
	 public:
		lbOpenGLIndexBuffer(uint32_t *indices, uint32_t count);
		~lbOpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		[[nodiscard]] uint32_t GetCount() const override {return m_Count;}
	 private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

} // Lambix
