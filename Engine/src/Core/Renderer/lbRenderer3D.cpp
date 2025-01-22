/**
 ***************************************************************
 * @file            : lbRenderer3D.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#include "Core/Renderer/lbRenderer3D.h"
#include <Core/Renderer/lbRendererCommand.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Lambix
{
	struct lbRenderer3DStorage
	{
		std::shared_ptr<lbVertexArray> cubeVao;
		std::shared_ptr<lbShaderProgram> shaderBaseTexture;
		std::shared_ptr<lbTexture> WhiteTexture;
		// temp
		glm::mat4 m_ViewProjectionMatrix{glm::mat4(1.0f)};
	};
	static std::unique_ptr<lbRenderer3DStorage> s_lbRenderer3DStorage;

	void lbRenderer3D::Init()
	{
		s_lbRenderer3DStorage = std::make_unique<lbRenderer3DStorage>();
		// cubeVao
		s_lbRenderer3DStorage->cubeVao = CreateCubeVertexArray();
		// shaderBaseTexture
		{
			s_lbRenderer3DStorage->shaderBaseTexture = lbShaderProgram::Create();
			std::shared_ptr<lbShader> vertexShader = lbShader::Create(lbShaderType::Vertex);
			std::shared_ptr<lbShader> fragmentShader = lbShader::Create(lbShaderType::Fragment);
			vertexShader->CompileFromFile("../Resources/Shaders/Vertex/baseTexture.vert");
			fragmentShader->CompileFromFile("../Resources/Shaders/Fragment/baseTexture.frag");
			s_lbRenderer3DStorage->shaderBaseTexture->Link(vertexShader, fragmentShader);
		}
		// WhiteTexture
		{
			s_lbRenderer3DStorage->WhiteTexture = lbTexture::Create(1,1);
			uint32_t WhiteTextureData = 0xffffffff;
			s_lbRenderer3DStorage->WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));
		}
	}
	void lbRenderer3D::BeginScene(const glm::mat4& viewProjectionMatrix)
	{
		s_lbRenderer3DStorage->m_ViewProjectionMatrix = viewProjectionMatrix;
	}
	void lbRenderer3D::EndScene()
	{
	}
	void lbRenderer3D::DrawCube(const glm::vec3& position,
								const glm::vec3& scale,
								const glm::vec3& rotation,
								const glm::vec4& color)
	{
		s_lbRenderer3DStorage->shaderBaseTexture->Bind();
		{
			s_lbRenderer3DStorage->WhiteTexture->Bind();
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformInt("Texture", 0);
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformFloat4("Color" ,color);
		}
		{
			auto model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕x轴旋转
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕y轴旋转
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕z轴旋转
			model = glm::scale(model, scale);
			// MVP传给着色器
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformMat4("MVP", s_lbRenderer3DStorage->m_ViewProjectionMatrix * model);
		}
		lbRendererCommand::DrawIndexed(s_lbRenderer3DStorage->cubeVao);
	}
	void lbRenderer3D::DrawCube(const glm::vec3& position,
								const glm::vec3& scale,
								const glm::vec3& rotation,
								const std::shared_ptr<lbTexture>& texture)
	{
		s_lbRenderer3DStorage->shaderBaseTexture->Bind();
		{
			texture->Bind();
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformInt("Texture", 0);
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformFloat4("Color" ,glm::vec4(1.0f));
		}
		{
			auto model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕x轴旋转
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕y轴旋转
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕z轴旋转
			model = glm::scale(model, scale);
			// MVP传给着色器
			s_lbRenderer3DStorage->shaderBaseTexture->UploadUniformMat4("MVP", s_lbRenderer3DStorage->m_ViewProjectionMatrix * model);
		}
		lbRendererCommand::DrawIndexed(s_lbRenderer3DStorage->cubeVao);
	}
	std::shared_ptr<lbVertexArray> lbRenderer3D::CreateCubeVertexArray()
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		uint32_t indices[36];
		for(int i = 0; i < 36; ++i)
		{
			indices[i] = i;
		}
		std::shared_ptr<lbVertexBuffer> vbo = lbVertexBuffer::Create(vertices, sizeof(vertices));
		lbBufferLayout layout = {
			{"position", lbShaderDataType::Float3},
			{"uv",    	 lbShaderDataType::Float2}
		};
		vbo->SetLayout(layout);
		std::shared_ptr<lbIndexBuffer> ebo = lbIndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));

		std::shared_ptr<lbVertexArray> cubeVao = lbVertexArray::Create();
		cubeVao->AddVertexBuffer(vbo);
		cubeVao->SetIndexBuffer(ebo);
		return cubeVao;
	}
}
