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
		~lbEditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(lbTimestep ts) override;
		virtual void OnImGuiRender() override;

	private:
		void AddPointLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &posiiton, const glm::vec3 &color,
						   const glm::vec2 &range = {0.001f, 10.f}, float intensity = 1.0f);

		void AddDirectionLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &direction, const glm::vec3 &color, float intensity = 0.2f);

		void AddSpotLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &posiiton, const glm::vec3 &lookAt,
						  const glm::vec3 &color, float intensity = 1.0f, const glm::vec2 &range = {0.001f, 20.f}, const glm::vec2 &angle = {0.01f, 30.f});

	private:
		std::shared_ptr<lbScene> m_Scene;
		std::vector<lbPanel::Ptr> m_Panels;
	};
}
