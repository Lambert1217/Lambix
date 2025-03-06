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
#include "Log/lbLog.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "GLFW/glfw3.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLContext.h"
#endif

namespace Lambix{

	lbGLFWWindow::lbGLFWWindow(uint32_t width, uint32_t height, const std::string& windowTitle)
	{
		// glfw 初始化
		if(!glfwInit()){
			LOG_CRITICAL("GLFW initialization failed!");
			return;
		}

		// m_Date 设置
		{
			m_Data.Width = width;
			m_Data.Height = height;
			m_Data.Title = windowTitle;
			m_Data.VSync = true;  // 默认开启垂直同步
		}

		// 创建窗口
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		LOG_ASSERT(m_Window, "GLFWwindow creation failed!");

		// 设置上下文
#ifdef LAMBIX_USE_OPENGL
		m_Context = new lbOpenGLContext(m_Window);
#endif
		m_Context->Init();

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

		LOG_INFO("Window initialization:({0},{1},{2})", m_Data.Width, m_Data.Height, m_Data.Title);
	}

	lbGLFWWindow::~lbGLFWWindow()
	{
		destroy();
	}

	void Lambix::lbGLFWWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Lambix::lbGLFWWindow::destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void lbGLFWWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
	bool lbGLFWWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	uint32_t lbGLFWWindow::GetWidth() const
	{
		return m_Data.Width;
	}
	uint32_t lbGLFWWindow::GetHeight() const
	{
		return m_Data.Height;
	}
	void lbGLFWWindow::SetMaximized()
	{
		glfwMaximizeWindow(m_Window);
	}
}
