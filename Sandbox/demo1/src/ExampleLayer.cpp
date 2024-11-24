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
ExampleLayer::ExampleLayer(): Lambix::lbLayer("Example"), m_ClearColor(1.0f, 0.8f, 0.8f, 1.0f)
{
}
void ExampleLayer::OnAttach()
{
	{
		float vertices[] = {
			-0.75f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.75f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f };
		uint32_t indices[] = { 0, 1, 2, 1, 2, 3 };
		std::shared_ptr<lbVertexBuffer> vbo = lbVertexBuffer::Create(vertices, sizeof(vertices));
		lbBufferLayout layout = {
			{"position", lbShaderDataType::Float3},
			{"color",    lbShaderDataType::Float4}
		};
		vbo->SetLayout(layout);
		std::shared_ptr<lbIndexBuffer> ebo = lbIndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));

		vao = lbVertexArray::Create();
		vao->AddVertexBuffer(vbo);
		vao->SetIndexBuffer(ebo);
	}
	{
		shaderProgram = lbShaderProgram::Create();
		std::shared_ptr<lbShader> vertexShader = lbShader::Create(lbShaderType::Vertex);
		std::shared_ptr<lbShader> fragmentShader = lbShader::Create(lbShaderType::Fragment);
		vertexShader->CompileFromFile("Shaders/Vertex/base.vert");
		fragmentShader->CompileFromFile("Shaders/Fragment/base.frag");
		shaderProgram->Link(vertexShader, fragmentShader);
	}
}
void ExampleLayer::OnDetach()
{
}
void ExampleLayer::OnUpdate(Lambix::lbTimestep ts)
{
	lbRendererCommand::SetClearColor(m_ClearColor);
	lbRendererCommand::Clear();

	shaderProgram->Bind();
	lbRendererCommand::DrawIndexed(vao);

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
