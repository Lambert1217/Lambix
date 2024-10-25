/**
 ***************************************************************
 * @file            : lbApplication.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#include "Core/lbApplication.h"
#include "Core/lbLog.h"
#include "Core/lbWindow.h"
#include "Core/lbCore.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	lbApplication* lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication() : m_Window(nullptr)
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;
	}

	void lbApplication::init()
	{
		// 窗口初始化
		m_Window = lbWindow::Create(m_AppSettings.WindowWidth, m_AppSettings.WindowHeight, m_AppSettings.WindowTitle);
		m_Window->SetEventCallback(LB_BIND_EVENT_FN(lbApplication::OnEvent));
	}

	void lbApplication::run()
	{
		while (isRunning)
		{
			auto CurrentTime = (float)glfwGetTime();
			lbTimestep timestep = CurrentTime - LastFrameTime;
			LastFrameTime = CurrentTime;

			// 遍历各层级 执行更新
			for (lbLayer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}

			m_Window->pollEvents();
			//m_Window->swapBuffer();
		}

	}
	void lbApplication::quit()
	{
		m_Window->destroy();
		LOG_INFO("Program Quit");
	}

	void lbApplication::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LB_BIND_EVENT_FN(lbApplication::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LB_BIND_EVENT_FN(lbApplication::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.GetHandled())
				break;
		}
	}
	bool lbApplication::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}
	bool lbApplication::OnWindowResize(WindowResizeEvent& e)
	{
		LOG_TRACE("OnResize : ({0},{1})",e.GetWidth(), e.GetHeight());
		return false;
	}
	void lbApplication::PushLayer(lbLayer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void lbApplication::PushOverlay(lbLayer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
} // Lambix