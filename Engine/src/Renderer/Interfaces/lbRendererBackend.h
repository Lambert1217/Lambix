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
#include "Core/lbCore.h"

namespace Lambix
{
	class lbRendererBackend
	{
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4 &color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		// depth
		virtual void SetDepthTest(bool flag) = 0;
		virtual void SetDepthWrite(bool flag) = 0;
		virtual void SetDepthFunc(DepthFunc func) = 0;

		// blend
		virtual void SetBlend(bool flag) = 0;
		virtual void SetBlendFunc(BlendFactor src, BlendFactor dst) = 0;

		// cull face
		virtual void SetCullFace(bool flag) = 0;
		virtual void SetCullFace(CullFace face) = 0;
		virtual void SetFrontFace(FrontFace face) = 0;

		// Polygon
		virtual void SetPolygonMode(PolygonMode mode) = 0;

		// RenderState
		virtual void SetRenderState(const RenderState &state) = 0;

		// Draw
		virtual void DrawIndexed(DrawMode DrawMode, uint32_t count) = 0;
		virtual void DrawArray(DrawMode DrawMode, uint32_t count) = 0;
	};

} // Lambix
