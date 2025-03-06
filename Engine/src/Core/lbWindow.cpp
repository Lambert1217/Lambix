/**
 ***************************************************************
 * @file            : lbWindow.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/10/25
 ***************************************************************
 */
//

#include "lbWindow.h"

#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX
#include "Platform/Window/lbGLFWWindow.h"
#endif

namespace Lambix
{

	lbWindow *lbWindow::Create(uint32_t width, uint32_t height, const std::string &windowTitle)
	{
#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX
		return new lbGLFWWindow(width, height, windowTitle);
#else
		return nullptr;
#endif
	}

}