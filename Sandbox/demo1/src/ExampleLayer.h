/**
 ***************************************************************
 * @file            : ExampleLayer.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

#include "lbEngine.h"

 class ExampleLayer : public Lambix::lbLayer
{
  public:
	 ExampleLayer();
	 ~ExampleLayer() = default;

	 virtual void OnAttach() override;
	 virtual void OnDetach() override;
	 virtual void OnUpdate(Lambix::lbTimestep ts) override;
	 virtual void OnEvent(Lambix::Event& event) override;
	 virtual void OnImGuiRender() override;

  private:
	glm::vec4 m_ClearColor;
	glm::vec3 eyePosition;
	float time{0};
	std::shared_ptr<Lambix::lbTexture> dogTexture;
 };
