/**
 ***************************************************************
 * @file            : WindowsWindow.h
 * @author          : Lambert
 * @brief           : Windows平台窗口，使用glfw实现
 * @attention       : None
 * @data            : 2024/10/5
 ***************************************************************
 */
//

#pragma once

#include "Core/lbWindow.h"

class GLFWwindow;

namespace Lambix{

	class WindowsWindow : public lbWindow
	{
	 public:
		WindowsWindow() : m_Window(nullptr), m_Data() {};
		virtual ~WindowsWindow() = default;

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override;
		bool init(uint32_t width, uint32_t height, const std::string& windowTitle) override;
		void pollEvents() override;
		void swapBuffer() override;
		void destroy() override;

		[[nodiscard]] void* GetNativeWindow() const override{ return m_Window; }
	 private:
		GLFWwindow* m_Window;
		// 内部结构体 记录窗口属性
		struct WindowData
		{
			std::string Title;
			uint32_t Width{0}, Height{0};
			bool VSync{false};
			EventCallbackFn EventCallback;
		}m_Data;
	};
}
