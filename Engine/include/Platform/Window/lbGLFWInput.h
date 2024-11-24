/**
 ***************************************************************
 * @file            : WindowsInput.h
 * @author          : Lambert
 * @brief           : GLFW窗口输入处理
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#pragma once

#include "Core/Base/lbInput.h"

namespace Lambix
{

	class lbGLFWInput : public lbInput
	{
	 protected:
		bool IsKeyPressedHelp(int keycode) override;
		bool IsMouseButtonPressedHelp(int button) override;
		std::pair<float, float> GetMousePositionHelp() override;
		float GetMouseXHelp() override;
		float GetMouseYHelp() override;
	};

} // Lambix
