/**
 ***************************************************************
 * @file            : lbInput.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/10/25
 ***************************************************************
 */
//

#include "Core/Base/lbInput.h"

#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX
#include "Platform/Window/lbGLFWInput.h"
#endif

namespace Lambix{

#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX
	lbInput* lbInput::s_lbInput = new lbGLFWInput();
#else
	lbInput* lbInput::s_lbInput = nullptr;
#endif
	
}