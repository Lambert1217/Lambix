/**
 ***************************************************************
 * @file            : lbRendererCommand.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Core/Renderer/lbRendererCommand.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLBackend.h"
#endif

namespace Lambix
{
#ifdef LAMBIX_USE_OPENGL
	lbRendererBackend* lbRendererCommand::s_RendererBackend = new lbOpenGLBackend();
#endif
} // Lambix