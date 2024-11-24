/**
 ***************************************************************
 * @file            : lbOpenGLBackend.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Core/Renderer/lbRendererBackend.h"

namespace Lambix
{

	class lbOpenGLBackend : public lbRendererBackend
	{
	 public:
		void Init() override;
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void DrawIndexed(const std::shared_ptr<lbVertexArray>& vertexArray) override;
	};

} // Lambix
