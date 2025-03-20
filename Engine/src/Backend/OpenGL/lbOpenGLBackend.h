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

#include "Renderer/lbRendererCommand.h"

namespace Lambix
{
	class lbOpenGLBackend : public lbRendererBackend
	{
	public:
		// 基本接口
		void Init() override;
		void Clear() override;
		void SetClearColor(const glm::vec4 &color) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		// 深度测试
		void SetDepthTest(bool flag) override;
		void SetDepthWrite(bool flag) override;
		void SetDepthFunc(DepthFunc func) override;

		// 混合
		void SetBlend(bool flag) override;
		void SetBlendFunc(BlendFactor src, BlendFactor dst) override;

		// 面剔除
		void SetCullFace(bool flag) override;
		void SetCullFace(CullFace face) override;
		void SetFrontFace(FrontFace face) override;

		// 多边形模式
		void SetPolygonMode(PolygonMode mode) override;

		// 完整渲染状态
		void SetRenderState(const RenderState &state) override;

		// 绘制命令（更新参数列表）
		void DrawIndexed(DrawMode DrawMode, uint32_t count) override;
		void DrawArray(DrawMode DrawMode, uint32_t count) override;

	private:
		// 状态缓存（可选）
		struct
		{
			DepthFunc currentDepthFunc = DepthFunc::Less;
			BlendFactor currentSrcFactor = BlendFactor::SrcAlpha;
			BlendFactor currentDstFactor = BlendFactor::OneMinusSrcAlpha;
			// 其他缓存状态...
		} m_stateCache;
	};
}
