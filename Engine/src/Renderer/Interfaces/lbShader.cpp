/**
 ***************************************************************
 * @file            : lbShader.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/24
 ***************************************************************
 */
//

#include "lbShader.h"

#ifdef LAMBIX_USE_OPENGL
#include "Backend/OpenGL/lbOpenGLShader.h"
#endif

namespace Lambix
{
	std::shared_ptr<lbShader> lbShader::Create(lbShaderType type)
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLShader>(type);
#endif
	}

	std::shared_ptr<lbShaderProgram> lbShaderProgram::Create()
	{
#ifdef LAMBIX_USE_OPENGL
		return std::make_shared<lbOpenGLShaderProgram>();
#endif
	}
} // Lambix