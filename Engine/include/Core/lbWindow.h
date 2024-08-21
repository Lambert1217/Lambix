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

#include "Core/Events/Event.h"

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

		using EventCallbackFn = std::function<void(Event &)>;

		/**
		 * @brief 设置事件回调
		 * @param callback
		 */
		void SetEventCallback(const EventCallbackFn &callback){
			m_Data.EventCallback = callback;
		}

		/**
		 * @brief 获取窗口单例
		 * @return
		 */
		inline static lbWindow* GetInstance()
		{
			static std::unique_ptr<lbWindow> instance(new lbWindow());
			return instance.get();
		}

		/**
		 *
		 * @return
		 */
		inline GLFWwindow* GetNativeWindow()
		{
			return m_Window;
		}

		/**
		 *
		 * @param width
		 * @param height
		 * @param windowTitle
		 * @return 初始化成功返回true，反之返回false
		 */
		bool init(uint32_t width, uint32_t height,const std::string& windowTitle);

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
		GLFWwindow* m_Window;
		// 内部结构体 记录窗口属性
		struct WindowData
		{
			std::string Title;
			uint32_t Width{0}, Height{0};
			EventCallbackFn EventCallback;
		}m_Data;
	};

} // Lambix
