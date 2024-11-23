/**
 ***************************************************************
 * @file            : ExampleLayer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#include "ExampleLayer.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

using namespace Lambix;
ExampleLayer::ExampleLayer(): Lambix::lbLayer("Example")
{
}
void ExampleLayer::OnAttach()
{
}
void ExampleLayer::OnDetach()
{
}
void ExampleLayer::OnUpdate(Lambix::lbTimestep ts)
{
	lbRendererCommand::SetClearColor(m_ClearColor);
	lbRendererCommand::Clear();

	//LOG_TRACE((int)1.f/ts);
}
void ExampleLayer::OnEvent(Lambix::Event& event)
{
}
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Config");
	ImGui::Text("ClearColor");
	ImGui::ColorEdit4("Color Setting", glm::value_ptr(m_ClearColor));
	ImGui::End();
}
