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

#include "glad/glad.h"

namespace Lambix
{
	lbApplication* lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication() : m_Window(nullptr), m_ImguiLayer(nullptr)
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;
	}

	void lbApplication::Init()
	{
		// 窗口初始化
		m_Window = lbWindow::Create(m_AppSettings.WindowWidth, m_AppSettings.WindowHeight, m_AppSettings.WindowTitle);
		m_Window->SetVSync(m_AppSettings.VSync);
		m_Window->SetEventCallback(LB_BIND_EVENT_FN(lbApplication::OnEvent));

		// Imgui
		m_ImguiLayer = new lbImguiLayer();
		PushOverlay(m_ImguiLayer);
	}

	void lbApplication::Run()
	{
		while (isRunning)
		{
			{
				glClearColor(1.0f, 0.8f, 0.8f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
			}
			auto CurrentTime = (float)glfwGetTime();
			lbTimestep timestep = CurrentTime - LastFrameTime;
			LastFrameTime = CurrentTime;

			// 遍历各层级 执行更新
			for (lbLayer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}
			// imgui 绘制
			m_ImguiLayer->Begin();
			for (lbLayer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImguiLayer->End();

			m_Window->OnUpdate();
		}

	}
	void lbApplication::Quit()
	{
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