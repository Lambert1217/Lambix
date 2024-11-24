/**
 ***************************************************************
 * @file            : lbRendererBackend.h
 * @author          : Lambert
 * @brief           : 渲染后端接口
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "glm/glm.hpp"
#include "lbVertexArray.h"

namespace Lambix
{

	class lbRendererBackend
	{
	 public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4 &color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const std::shared_ptr<lbVertexArray>& vertexArray) = 0;
	};

} // Lambix
