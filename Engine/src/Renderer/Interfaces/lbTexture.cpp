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

#include "lbTexture.h"
#include "Log/lbLog.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLTexture.h"
#endif

namespace Lambix
{
	lbTexture2D::Ptr lbTexture2D::Create(const lbSource::Ptr &source, const lbTextureSpecification &spec)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLTexture2D>(source, spec);
#endif
		return nullptr;
	}

	lbTexture2D::Ptr lbTexture2D::Create(const std::vector<std::byte> &source, const lbTextureSpecification &spec)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLTexture2D>(source, spec);
#endif
	}

	lbTextureCube::Ptr lbTextureCube::Create(const std::array<lbSource::Ptr, 6> &sources, const lbTextureSpecification &spec)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLTextureCube>(sources, spec);
#endif
		return nullptr;
	}
}
