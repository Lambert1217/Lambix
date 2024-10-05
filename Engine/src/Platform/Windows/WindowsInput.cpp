/**
 ***************************************************************
 * @file            : WindowsInput.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#include "Platform/Windows/WindowsInput.h"
#include "Core/lbApplication.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	lbInput* lbInput::s_lbInput = new WindowsInput();

	bool WindowsInput::IsKeyPressedHelp(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedHelp(int button)
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionHelp()
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float WindowsInput::GetMouseXHelp()
	{
		return GetMousePositionHelp().first;
	}
	float WindowsInput::GetMouseYHelp()
	{
		return GetMousePositionHelp().second;
	}
} // Lambix