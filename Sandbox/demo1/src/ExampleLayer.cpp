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
}
void ExampleLayer::OnEvent(Lambix::Event& event)
{
}
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::Text("Hello Imgui!");
	ImGui::End();
}
