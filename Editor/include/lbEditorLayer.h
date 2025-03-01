/**
 * @file lbEditorLayer.h
 * @author Lambert1217 (1904310303@qq.com)
 * @brief 编辑器图层
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "lbEngine.h"

namespace Lambix
{
	class lbEditorLayer : public lbLayer
	{
	public:
		lbEditorLayer();
		~lbEditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(lbTimestep ts) override;
		virtual void OnEvent(Event &event) override;
		virtual void OnImGuiRender() override;

	private:
		std::shared_ptr<lbFrameBuffer> m_FrameBuffer;
		std::shared_ptr<lbScene> m_Scene;
	};
}
