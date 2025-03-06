/**
 ***************************************************************
 * @file            : lbOpenGLContext.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLContext.h"
#include "Log/lbLog.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	lbOpenGLContext::lbOpenGLContext(GLFWwindow* windowHandle)
	 	: m_WindowHandle(windowHandle)
	{
		LOG_ASSERT(m_WindowHandle, "m_WindowHandle is nullptr!");
	}
	void lbOpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// 加载Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LOG_ASSERT(status, "Failed to initialize Glad!");

		LOG_INFO("OpenGL Info:");
		LOG_INFO("  Vendor: {0}", (const char*)(glGetString(GL_VENDOR)));
		LOG_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LOG_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void lbOpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
} // Lambix