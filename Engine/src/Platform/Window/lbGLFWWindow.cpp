/**
 ***************************************************************
 * @file            : lbGLFWWindow.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#include "Platform/Window/lbGLFWWindow.h"
#include "Core/lbLog.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "GLFW/glfw3.h"

namespace Lambix{

	lbGLFWWindow::lbGLFWWindow(uint32_t width, uint32_t height, const std::string& windowTitle)
	{
		// glfw 初始化
		LOG_ASSERT(glfwInit(),"GLFW initialization failed!");
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// 创建窗口
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.Title = windowTitle;
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height,m_Data.Title.c_str(), nullptr, nullptr);
		LOG_ASSERT(m_Window, "GLFWwindow creation failed!");
		// 设置上下文
		glfwMakeContextCurrent(m_Window);

		// 通过 m_Window 传递 m_Data
		glfwSetWindowUserPointer(m_Window, &m_Data);

		//设置事件
		//窗口大小变化
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		  data.Width = width;
		  data.Height = height;
		  WindowResizeEvent event(width, height);
		  data.EventCallback(event);
		});
		//窗口关闭
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		  WindowCloseEvent event;
		  data.EventCallback(event);
		});
		//键盘事件
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		  switch (action)
		  {
		  case GLFW_PRESS:
		  {
			  KeyPressedEvent event(key, 0);
			  data.EventCallback(event);
			  break;
		  }
		  case GLFW_REPEAT:
		  {
			  KeyPressedEvent event(key, 1);
			  data.EventCallback(event);
			  break;
		  }
		  case GLFW_RELEASE:
		  {
			  KeyReleasedEvent event(key);
			  data.EventCallback(event);
			  break;
		  }
		  default:
			  break;
		  }
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		  KeyTypedEvent event((int)keycode);

		  data.EventCallback(event);
		});
		// 鼠标点击事件
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		  switch (action)
		  {
		  case GLFW_PRESS:
		  {
			  MouseButtonPressedEvent event(button);
			  data.EventCallback(event);
			  break;
		  }
		  case GLFW_RELEASE:
		  {
			  MouseButtonReleasedEvent event(button);
			  data.EventCallback(event);
			  break;
		  }
		  default:
			  break;
		  }
		});
		//鼠标滚轮事件
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		  MouseScrolledEvent event((float)xOffset, (float)yOffset);
		  data.EventCallback(event);
		});
		//鼠标移动事件
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
		  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		  MouseMovedEvent event((float)xPos, (float)yPos);
		  data.EventCallback(event);
		});

		LOG_INFO("Window initialization：({0},{1},{2})",m_Data.Width, m_Data.Height, m_Data.Title);
	}

	void Lambix::lbGLFWWindow::pollEvents()
	{
		glfwPollEvents();
	}

	void Lambix::lbGLFWWindow::destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		LOG_INFO("Window Destruction");
	}
}
