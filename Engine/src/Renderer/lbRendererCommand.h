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

#include "Renderer/Interfaces/lbRendererBackend.h"

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
		inline static void DrawIndexed(DrawMode DrawMode, uint32_t count)
		{
			s_RendererBackend->DrawIndexed(DrawMode, count);
		}
		inline static void DrawArray(DrawMode DrawMode, uint32_t count)
		{
			s_RendererBackend->DrawArray(DrawMode, count);
		}
		inline static void SetDepthTest(bool flag)
		{
			s_RendererBackend->SetDepthTest(flag);
		}
		inline static void SetDepthWrite(bool flag)
		{
			s_RendererBackend->SetDepthWrite(flag);
		}
		inline static void SetDepthFunc(DepthFunc func)
		{
			s_RendererBackend->SetDepthFunc(func);
		}

		inline static void SetBlend(bool flag)
		{
			s_RendererBackend->SetBlend(flag);
		}
		inline static void SetBlendFunc(BlendFactor src, BlendFactor dst)
		{
			s_RendererBackend->SetBlendFunc(src, dst);
		}

		inline static void SetCullFace(bool flag)
		{
			s_RendererBackend->SetCullFace(flag);
		}
		inline static void SetCullFace(CullFace face)
		{
			s_RendererBackend->SetCullFace(face);
		}
		inline static void SetFrontFace(FrontFace face)
		{
			s_RendererBackend->SetFrontFace(face);
		}

		inline static void SetPolygonMode(PolygonMode mode)
		{
			s_RendererBackend->SetPolygonMode(mode);
		}

		inline static void SetRenderState(const RenderState &state)
		{
			s_RendererBackend->SetRenderState(state);
		}

	 private:
		static lbRendererBackend* s_RendererBackend;
	};

} // Lambix
