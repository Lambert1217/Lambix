/**
 ***************************************************************
 * @file            : lbWindow.h
 * @author          : Lambert
 * @brief           : 窗口基类
 * @attention       : None
 * @data            : 2024/8/20
 ***************************************************************
 */
//

#pragma once

#include "Core/Events/Event.h"

namespace Lambix
{
	class lbWindow
	{
	 public:
		~lbWindow() = default;

		using EventCallbackFn = std::function<void(Event &)>;

		/**
		 * @brief 设置事件回调
		 * @param callback
		 */
		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

		/**
		 * @brief 设置垂直同步
		 * @param enabled
		 */
		virtual void SetVSync(bool enabled) = 0;

		/**
		 * @brief 返回是否开启垂直同步
		 * @return
		 */
		[[nodiscard]] virtual bool IsVSync() const = 0;

		/**
		 *
		 * @param width
		 * @param height
		 * @param windowTitle
		 * @return 初始化成功返回true，反之返回false
		 */
		virtual bool init(uint32_t width, uint32_t height,const std::string& windowTitle) = 0;

		/**
		 * @brief 事件轮询
		 */
		virtual void pollEvents() = 0;

		/**
		 * @brief 切换双缓存
		 */
		virtual void swapBuffer() = 0;

		/**
		 * @brief 窗口销毁，卸载资源
		 */
		virtual void destroy() = 0;

		/**
		 * @brief 获取活动窗口
		 * @return
		 */
		[[nodiscard]] virtual void *GetNativeWindow() const = 0;

		/**
		 * @brief 窗口创建
		 */
		static lbWindow* Create(uint32_t width = 1280, uint32_t height = 720, const std::string& windowTitle = "Lambix Engine");
	};


} // Lambix
