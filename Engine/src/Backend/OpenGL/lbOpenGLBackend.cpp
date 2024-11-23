/**
 ***************************************************************
 * @file            : lbOpenGLBackend.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLBackend.h"

#include "glad/glad.h"

namespace Lambix
{
	void lbOpenGLBackend::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}
	void lbOpenGLBackend::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void lbOpenGLBackend::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}
	void lbOpenGLBackend::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
} // Lambix