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

#include "Platform/Window/lbGLFWInput.h"
#include "Core/Base/lbApplication.h"
#include "GLFW/glfw3.h"

namespace Lambix
{
	bool lbGLFWInput::IsKeyPressedHelp(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool lbGLFWInput::IsMouseButtonPressedHelp(int button)
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> lbGLFWInput::GetMousePositionHelp()
	{
		auto window = static_cast<GLFWwindow*>(lbApplication::GetInstance().GetWindow()->GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float lbGLFWInput::GetMouseXHelp()
	{
		return GetMousePositionHelp().first;
	}
	float lbGLFWInput::GetMouseYHelp()
	{
		return GetMousePositionHelp().second;
	}
} // Lambix