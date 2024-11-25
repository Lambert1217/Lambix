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

#include "Core/Base/lbApplication.h"
#include "Core/Base/lbLog.h"
#include "Core/Base/lbWindow.h"
#include "Core/Base/lbCore.h"
#include "GLFW/glfw3.h"
#include "Core/Renderer/lbRenderer3D.h"
#include "Core/Renderer/lbRendererCommand.h"

namespace Lambix
{
	lbApplication* lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication() : m_Window(nullptr), m_ImguiLayer(nullptr)
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;

		Init();
	}

	void lbApplication::Init()
	{
		// 窗口初始化
		m_Window = lbWindow::Create(m_AppSettings.WindowWidth, m_AppSettings.WindowHeight, m_AppSettings.WindowTitle);
		m_Window->SetVSync(m_AppSettings.VSync);
		m_Window->SetEventCallback(LB_BIND_EVENT_FN(lbApplication::OnEvent));

		// 渲染初始
		lbRendererCommand::Init();
		lbRenderer3D::Init();

		// Imgui
		m_ImguiLayer = new lbImguiLayer();
		PushOverlay(m_ImguiLayer);
	}

	void lbApplication::Run()
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
		lbRendererCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
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