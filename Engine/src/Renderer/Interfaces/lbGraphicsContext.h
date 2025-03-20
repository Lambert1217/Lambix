/**
 ***************************************************************
 * @file            : GraphicsContext.h
 * @author          : Lambert
 * @brief           : 上下文
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{

	class lbGraphicsContext
	{
	 public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

} // Lambix
