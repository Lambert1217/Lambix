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

#include "Application/lbApplication.h"
#include "Debug/lbLog.h"
#include "Window/lbWindow.h"

namespace Lambix
{
	lbApplication* lbApplication::s_lbApplication = nullptr;

	lbApplication::lbApplication()
	{
		LOG_ASSERT(!s_lbApplication, "lbApplication already exists");
		s_lbApplication = this;

		// 窗口初始化
		WINDOW->init(1280, 720, "Lambix");
	}

	void lbApplication::run()
	{
		while (!WINDOW->shouldClose())
		{
			WINDOW->pollEvents();
			WINDOW->swapBuffer();
		}
	}
	void lbApplication::quit()
	{
		WINDOW->destroy();
		LOG_INFO("Program Quit");
	}
} // Lambix