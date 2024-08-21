/**
 ***************************************************************
 * @file            : lbInput.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#include "Core/lbInput.h"
#include "Core/lbWindow.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	lbInput* lbInput::s_lbInput = new lbInput();

	bool lbInput::IsKeyPressedHelp(int keycode)
	{
		auto state = glfwGetKey(WINDOW->GetNativeWindow(), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool lbInput::IsMouseButtonPressedHelp(int button)
	{
		auto state = glfwGetMouseButton(WINDOW->GetNativeWindow(), button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> lbInput::GetMousePositionHelp()
	{
		double xpos, ypos;
		glfwGetCursorPos(WINDOW->GetNativeWindow(), &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float lbInput::GetMouseXHelp()
	{
		return GetMousePositionHelp().first;
	}
	float lbInput::GetMouseYHelp()
	{
		return GetMousePositionHelp().second;
	}
} // Lambix