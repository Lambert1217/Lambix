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
#include "Core/lbInput.h"

namespace Lambix
{
	lbApplication* lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication()
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;

		// 窗口初始化
		WINDOW->init(1280, 720, "Lambix");
		WINDOW->SetEventCallback(LB_BIND_EVENT_FN(lbApplication::OnEvent));
	}

	void lbApplication::run()
	{
		while (isRunning)
		{
			WINDOW->pollEvents();

			if(lbInput::IsKeyPressed(LB_KEY_W))
			{
				LOG_TRACE("W");
			}
			if(lbInput::IsMouseButtonPressed(LB_MOUSE_BUTTON_1))
			{
				LOG_TRACE("MouseButton 1");
			}
			//LOG_TRACE("MousePosition : ({0}, {1})", lbInput::GetMousePosition().first, lbInput::GetMousePosition().second);

			WINDOW->swapBuffer();
		}

	}
	void lbApplication::quit()
	{
		WINDOW->destroy();
		LOG_INFO("Program Quit");
	}

	void lbApplication::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LB_BIND_EVENT_FN(lbApplication::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LB_BIND_EVENT_FN(lbApplication::OnWindowResize));

//		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
//		{
//			(*--it)->OnEvent(e);
//			if (e.GetHandled())
//				break;
//		}
	}
	bool lbApplication::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		quit();
		return true;
	}
	bool lbApplication::OnWindowResize(WindowResizeEvent& e)
	{
		LOG_TRACE("OnResize : ({0},{1})",e.GetWidth(), e.GetHeight());
		return false;
	}
} // Lambix