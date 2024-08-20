/**
 ***************************************************************
 * @file            : lbWindow.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/20
 ***************************************************************
 */
//

#include "Window/lbWindow.h"
#include "Debug/lbLog.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	lbWindow* lbWindow::s_lbWindow = nullptr;

	lbWindow* lbWindow::GetInstance()
	{
		if(s_lbWindow == nullptr)
		{
			s_lbWindow = new lbWindow();
		}
		return s_lbWindow;
	}

	lbWindow::lbWindow():m_Width(0), m_Height(0),m_Window(nullptr),m_WindowTitle()
	{
	}

	bool lbWindow::init(uint32_t width, uint32_t height, const std::string& windowTitle)
	{
		// glfw 初始化
		if(!glfwInit()){
			LOG_ERROR("glfw 初始化失败！");
			return false;
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // 创建窗口
		m_Width = width;
		m_Height = height;
		m_WindowTitle = windowTitle;
		m_Window = glfwCreateWindow(m_Width, m_Height,m_WindowTitle.c_str(), nullptr, nullptr);
		if(!m_Window){
			LOG_ERROR("窗口创建失败！");
			return false;
		}
		// 设置上下文
		glfwMakeContextCurrent(m_Window);

		LOG_INFO("窗口初始化：({0},{1},{2})",m_Width, m_Height, m_WindowTitle);
		return true;
	}

	bool lbWindow::shouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void lbWindow::pollEvents()
	{
		glfwPollEvents();
	}

	void lbWindow::swapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void lbWindow::destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		LOG_INFO("窗口销毁");
	}

} // Lambix