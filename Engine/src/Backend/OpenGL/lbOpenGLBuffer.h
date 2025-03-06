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

#include "Renderer/lbBuffer.h"

namespace Lambix
{

	class lbOpenGLVertexBuffer : public lbVertexBuffer
	{
	public:
		lbOpenGLVertexBuffer(void *data, uint32_t size, const lbBufferElement &element);
		~lbOpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		void *GetData() const override { return m_Data; }
		uint32_t GetDataSize() const override { return m_Size; }

		[[nodiscard]] const lbBufferElement &GetElement() const override { return m_Element; }

	private:
		uint32_t m_RendererID;
		lbBufferElement m_Element;
		void *m_Data;
		uint32_t m_Size;
	};

	class lbOpenGLIndexBuffer : public lbIndexBuffer
	{
	public:
		lbOpenGLIndexBuffer(uint32_t *indices, uint32_t count);
		~lbOpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		[[nodiscard]] uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

} // Lambix
