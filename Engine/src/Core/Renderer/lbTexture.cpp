/**
 ***************************************************************
 * @file            : lbTexture.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#include "Core/Renderer/lbTexture.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLTexture.h"
#endif

namespace Lambix
{

	std::shared_ptr<lbTexture> lbTexture::Create(const std::string& path)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLTexture>(path);
#endif
	}
	std::shared_ptr<lbTexture> lbTexture::Create(uint32_t width, uint32_t height)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLTexture>(width, height);
#endif
	}
}
