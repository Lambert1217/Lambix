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
#include "Panels/lbPanel.h"

namespace Lambix
{
	class lbEditorLayer : public lbLayer
	{
	public:
		lbEditorLayer();
		~lbEditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(lbTimestep ts) override;
		virtual void OnImGuiRender() override;

	private:
		void OnOpenProject(const lbEvent::Ptr &event);

	private:
		lbProject *mCurrentProject{nullptr};
		std::unordered_map<std::string, lbPanel::Ptr> m_Panels;
	};
}
