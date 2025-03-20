/**
 ***************************************************************
 * @file            : lbBuffer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "lbBuffer.h"
#include "Log/lbLog.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLBuffer.h"
#endif

namespace Lambix
{
	lbBuffer::Ptr lbBuffer::Create(const lbBufferSpecification &spec)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLBuffer>(spec);
#endif
		return nullptr;
	}
} // Lambix