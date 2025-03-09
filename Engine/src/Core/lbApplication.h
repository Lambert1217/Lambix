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

#include "lbWindow.h"
#include "lbLayerStack.h"
#include "Imgui/lbImguiLayer.h"
#include "Events/lbEvent.h"

namespace Lambix
{
	struct lbAppSettings
	{
		uint32_t WindowWidth{1280};
		uint32_t WindowHeight{960};
		std::string WindowTitle{"Lambix Engine"};
		bool VSync{true};
	};

	class lbApplication
	{
	public:
		lbApplication(const lbAppSettings &appSettings = lbAppSettings());
		virtual ~lbApplication();

		/**
		 * @brief 程序初始化
		 */
		void Init(const lbAppSettings &appSettings);

		/**
		 * @brief 程序执行
		 */
		void Run();

		/**
		 * @brief 程序退出
		 */
		void Quit();

		/**
		 * 获取程序单例
		 * @return
		 */
		inline static lbApplication &GetInstance() { return *s_lbApplication; }

		/**
		 * 普通层入栈
		 * @param layer
		 */
		void PushLayer(lbLayer *layer);

		/**
		 * 覆盖层入栈
		 * @param overlay
		 */
		void PushOverlay(lbLayer *overlay);

		[[nodiscard]] inline lbWindow *GetWindow() const { return m_Window; }
		inline lbAppSettings &GetAppSetting() { return m_AppSettings; }
		inline const lbAppSettings &GetAppSetting() const { return m_AppSettings; }

	private:
		void OnWindowResize(const lbEvent::Ptr &event);
		void OnWindowClose(const lbEvent::Ptr &event);

	private:
		static lbApplication *s_lbApplication; // 应用类单例
		lbAppSettings m_AppSettings;
		lbWindow *m_Window;
		lbImguiLayer *m_ImguiLayer;
		bool isRunning{true};
		bool isMinsize{false};
		lbLayerStack m_LayerStack;
		float LastFrameTime{0.0f};
	};

	/**
	 * @brief 创建程序,由使用者实现
	 * @return
	 */
	lbApplication *CreateApplication();

} // Lambix
