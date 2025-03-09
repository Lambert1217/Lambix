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
#include "Renderer/lbGraphicsContext.h"

class GLFWwindow;

namespace Lambix
{

	class lbGLFWWindow : public lbWindow
	{
	public:
		lbGLFWWindow(uint32_t width, uint32_t height, const std::string &windowTitle);
		virtual ~lbGLFWWindow();

		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		void SetMaximized() override;
		bool IsVSync() const override;
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

		[[nodiscard]] void *GetNativeWindow() const override { return m_Window; }

	private:
		void destroy();

	private:
		GLFWwindow *m_Window;
		lbGraphicsContext *m_Context;

		// 内部结构体 记录窗口属性
		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;					   // 是否开启垂直同步
			bool Maximized;				   // 是否最大化
			lbGLFWWindow *Self{nullptr};   // 存储自身的指针，派发事件时使用
		} m_Data;
	};
}
