/**
 ***************************************************************
 * @file            : lbRenderer3D.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#pragma once

#include "lbVertexArray.h"
#include "Core/Renderer/lbTexture.h"
#include "Core/Renderer/lbShader.h"
#include "glm/glm.hpp"

namespace Lambix
{
	class lbRenderer3D
	{
	 public:
		static void Init();

		static void BeginScene(const glm::mat4& viewProjectionMatrix);
		static void EndScene();

		static void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const glm::vec4& color);
		static void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const std::shared_ptr<lbTexture>& texture);
	 private:
		static std::shared_ptr<lbVertexArray> CreateCubeVertexArray();
	};
}
