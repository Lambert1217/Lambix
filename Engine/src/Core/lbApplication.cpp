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

#include "lbApplication.h"
#include "Log/lbLog.h"
#include "Core/lbWindow.h"
#include "Core/lbCore.h"
#include "GLFW/glfw3.h"
#include "Renderer/lbRendererCommand.h"

namespace Lambix
{
	lbApplication *lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication(const lbAppSettings &appSettings) : m_Window(nullptr), m_ImguiLayer(nullptr)
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;

		Init(appSettings);
	}

	lbApplication::~lbApplication()
	{
		// 移除事件监听
		lbEventDispatcher::Get()->removeEventListener<lbApplication>("WindowResize", this, &lbApplication::OnWindowResize);
		lbEventDispatcher::Get()->removeEventListener<lbApplication>("WindowClose", this, &lbApplication::OnWindowClose);
	}

	void lbApplication::Init(const lbAppSettings &appSettings)
	{
		m_AppSettings = appSettings;
		// 窗口初始化
		m_Window = lbWindow::Create(m_AppSettings.WindowWidth, m_AppSettings.WindowHeight, m_AppSettings.WindowTitle);
		m_Window->SetVSync(m_AppSettings.VSync);
		m_Window->SetMaximized();

		// 注册事件监听
		lbEventDispatcher::Get()->addEventListener<lbApplication>("WindowResize", this, &lbApplication::OnWindowResize);
		lbEventDispatcher::Get()->addEventListener<lbApplication>("WindowClose", this, &lbApplication::OnWindowClose);

		// 渲染初始
		lbRendererCommand::Init();

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

			// 如果没有最小化 遍历各层级 执行更新
			if (!isMinsize)
			{
				for (lbLayer *layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			}
			// imgui 绘制
			m_ImguiLayer->Begin();
			for (lbLayer *layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImguiLayer->End();

			m_Window->OnUpdate();
		}
	}
	void lbApplication::Quit()
	{
		isRunning = false;
		LOG_INFO("Program Quit");
	}
	void lbApplication::OnWindowResize(const lbEvent::Ptr &event)
	{
		int *size = static_cast<int *>(event->m_UserData);
		int width = size[0], height = size[1];
		if (width == 0 || height == 0)
		{
			isMinsize = true;
			return;
		}
		isMinsize = false;
		lbRendererCommand::SetViewport(0, 0, width, height);
	}
	void lbApplication::OnWindowClose(const lbEvent::Ptr &event)
	{
		Quit();
	}
	void lbApplication::PushLayer(lbLayer *layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void lbApplication::PushOverlay(lbLayer *overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
} // Lambix