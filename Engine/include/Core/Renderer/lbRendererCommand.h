/**
 ***************************************************************
 * @file            : lbRendererCommand.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "lbRendererBackend.h"

namespace Lambix
{

	class lbRendererCommand
	{
	 public:
		inline static void Init()
		{
			s_RendererBackend->Init();
		}
		inline static void Clear()
		{
			s_RendererBackend->Clear();
		}
		inline static void SetClearColor(const glm::vec4 &color)
		{
			s_RendererBackend->SetClearColor(color);
		}
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererBackend->SetViewport(x, y, width, height);
		}
		inline static void DrawIndexed(const std::shared_ptr<lbVertexArray>& vertexArray)
		{
			s_RendererBackend->DrawIndexed(vertexArray);
		}
	 private:
		static lbRendererBackend* s_RendererBackend;
	};

} // Lambix
