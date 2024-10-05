/**
 ***************************************************************
 * @file            : WindowsInput.h
 * @author          : Lambert
 * @brief           : Windows平台输入处理
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#pragma once

#include "Core/lbInput.h"

namespace Lambix
{

	class WindowsInput : public lbInput
	{
	 protected:
		bool IsKeyPressedHelp(int keycode) override;
		bool IsMouseButtonPressedHelp(int button) override;
		std::pair<float, float> GetMousePositionHelp() override;
		float GetMouseXHelp() override;
		float GetMouseYHelp() override;
	};

} // Lambix
