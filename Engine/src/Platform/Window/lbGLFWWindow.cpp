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
#include "GLFW/glfw3.h"
#include "Events/lbEventPool.h"

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
			m_Data.Self = this;
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
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
								  {
									// 先更新数据
									WindowData &windowData = *(WindowData *)glfwGetWindowUserPointer(window);
									windowData.Width = width;
									windowData.Height = height;
									// 构造事件派发
									lbEvent::Ptr event = lbEventPool::Get()->Acquire();
									std::vector<int> newWindowSize = {width, height};
									event->Set("WindowResize", windowData.Self, newWindowSize.data());
									lbEventDispatcher::Get()->dispatchEvent(event); });
		//窗口关闭
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
								   {
									WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
									// 构造事件派发
									lbEvent::Ptr event = lbEventPool::Get()->Acquire();
									event->Set("WindowClose", windowData.Self);
									lbEventDispatcher::Get()->dispatchEvent(event); });

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
