/**
 ***************************************************************
 * @file            : lbOpenGLContext.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Renderer/lbGraphicsContext.h"

class GLFWwindow;

namespace Lambix
{

	class lbOpenGLContext : public lbGraphicsContext
	{
	public:
		lbOpenGLContext(GLFWwindow *windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow *m_WindowHandle;
	};

} // Lambix
