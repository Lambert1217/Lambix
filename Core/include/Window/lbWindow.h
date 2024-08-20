/**
 ***************************************************************
 * @file            : lbWindow.h
 * @author          : Lambert
 * @brief           : 基于glfw的窗口
 * @attention       : None
 * @data            : 2024/8/20
 ***************************************************************
 */
//

#pragma once

#include "string"

#define WINDOW Lambix::lbWindow::GetInstance()
class GLFWwindow;

namespace Lambix
{

	class lbWindow
	{
	 public:
		lbWindow(const lbWindow&) = delete;
		lbWindow &operator=(const lbWindow&) = delete;
		~lbWindow() = default;

		/**
		 * @brief 获取窗口单例
		 * @return
		 */
		static lbWindow* GetInstance();

		/**
		 *
		 * @param width
		 * @param height
		 * @param windowTitle
		 * @return 初始化成功返回true，反之返回false
		 */
		bool init(uint32_t width, uint32_t height,const std::string& windowTitle);
		/**
		 *
		 * @return 窗口应该关闭时返回true，反之返回false
		 */
		bool shouldClose();

		/**
		 * @brief 事件轮询
		 */
		void pollEvents();

		/**
		 * @brief 切换双缓存
		 */
		void swapBuffer();

		/**
		 * @brief 窗口销毁，卸载glfw资源
		 */
		void destroy();
	 private:
		lbWindow();
	 private:
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_WindowTitle;
		GLFWwindow* m_Window;
		static lbWindow* s_lbWindow;
	};

} // Lambix
