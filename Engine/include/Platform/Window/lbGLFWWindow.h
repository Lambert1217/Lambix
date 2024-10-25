/**
 ***************************************************************
 * @file            : WindowsWindow.h
 * @author          : Lambert
 * @brief           : GLFW窗口实现
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#pragma once

#include "Core/lbWindow.h"

class GLFWwindow;

namespace Lambix{

	class lbGLFWWindow : public lbWindow
	{
	 public:
		lbGLFWWindow(uint32_t width, uint32_t height, const std::string& windowTitle);
		virtual ~lbGLFWWindow() = default;

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void pollEvents() override;
		void destroy() override;

		[[nodiscard]] void* GetNativeWindow() const override{ return m_Window; }
	 private:
		GLFWwindow* m_Window;
		// 内部结构体 记录窗口属性
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			EventCallbackFn EventCallback;
		}m_Data;
	};
}
