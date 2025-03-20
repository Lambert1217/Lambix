/**
 ***************************************************************
 * @file            : lbVertexArray.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "lbVertexArray.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLVertexArray.h"
#endif

namespace Lambix
{
	std::shared_ptr<lbVertexArray> lbVertexArray::Create()
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLVertexArray>();
#endif
	}
} // Lambix