/**
 ***************************************************************
 * @file            : lbApplication.h
 * @author          : Lambert
 * @brief           : 控制程序循环
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

#include "Core/Events/ApplicationEvent.h"
#include "Core/lbWindow.h"
#include "lbLayerStack.h"

namespace Lambix
{

	class lbApplication
	{
	 public:
		lbApplication();
		virtual ~lbApplication() = default;

		/**
		 * @brief 程序执行
		 */
		void run();

		/**
		 * @brief 程序退出
		 */
		void quit();

		/**
		 * 获取程序单例
		 * @return
		 */
		inline static lbApplication& GetInstance() { return *s_lbApplication; }

		/**
		 * @brief 事件处理
		 * @param e
		 */
		void OnEvent(Event& e);

		/**
		 * 普通层入栈
		 * @param layer
		 */
		void PushLayer(lbLayer* layer);

		/**
		 * 覆盖层入栈
		 * @param overlay
		 */
		void PushOverlay(lbLayer* overlay);

		[[nodiscard]] inline lbWindow* GetWindow() const { return m_Window; }
	 private:
		bool OnWindowClose(WindowCloseEvent& e); // 窗口关闭事件处理函数
		bool OnWindowResize(WindowResizeEvent& e); // 窗口关闭事件处理函数

	 private:
		static lbApplication* s_lbApplication; // 应用类单例
		lbWindow* m_Window;
		bool isRunning{true};
		lbLayerStack m_LayerStack;
		float LastFrameTime{ 0.0f };
	};

	/**
	 * @brief 创建程序,由使用者实现
	 * @return
	 */
	lbApplication* CreateApplication();

} // Lambix
