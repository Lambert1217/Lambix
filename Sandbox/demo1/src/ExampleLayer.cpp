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
ExampleLayer::ExampleLayer(): Lambix::lbLayer("Example"),
	m_ClearColor(1.0f, 0.8f, 0.8f, 1.0f), eyePosition(0.f, 0.f, -5.f)
{
}
void ExampleLayer::OnAttach()
{
	dogTexture = lbTexture::Create("Resources/Textures/dog.png");
}
void ExampleLayer::OnDetach()
{
}
void ExampleLayer::OnUpdate(Lambix::lbTimestep ts)
{
	lbRendererCommand::SetClearColor(m_ClearColor);
	lbRendererCommand::Clear();

	// 计算MVP矩阵
	time += ts;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		(float)lbApplication::GetInstance().GetWindow()->GetWidth() / (float)lbApplication::GetInstance().GetWindow()->GetHeight(),
		0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(eyePosition, {0, 0, 0}, glm::vec3(0.0f, 1.0f, 0.0f));

	lbRenderer3D::BeginScene(projection * view);
	lbRenderer3D::DrawCube({-1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, {0.f, time*75, 0.f}, {0.3f, 0.4f, 0.5f, 1.f});
	lbRenderer3D::DrawCube({1.f, 0.f, 0.f}, {1.f, 1.f, 1.f}, {0.f, -time*100, 0.f}, dogTexture);
	lbRenderer3D::EndScene();
}
void ExampleLayer::OnEvent(Lambix::Event& event)
{
}
void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Config");
	ImGui::Text("ClearColor");
	ImGui::ColorEdit4("Color Setting", glm::value_ptr(m_ClearColor));
	ImGui::Text("Eye");
	ImGui::SliderFloat3("EyePosition", glm::value_ptr(eyePosition), -10.f, 10.f);
	ImGui::End();
}
