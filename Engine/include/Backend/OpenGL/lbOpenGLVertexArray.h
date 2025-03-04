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

#include "Core/Renderer/lbVertexArray.h"

namespace Lambix
{

	class lbOpenGLVertexArray : public lbVertexArray
	{
	 public:
		lbOpenGLVertexArray();
		~lbOpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<lbVertexBuffer> vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<lbIndexBuffer> indexBuffer) override;

		const std::vector<std::shared_ptr<lbVertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers;}
		const std::shared_ptr<lbIndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;}
	 private:
		std::vector<std::shared_ptr<lbVertexBuffer>> m_VertexBuffers;
		std::shared_ptr<lbIndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};

} // Lambix
