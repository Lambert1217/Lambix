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
		 * @brief 事件轮询
		 */
		virtual void pollEvents() = 0;

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
		static lbWindow* Create(uint32_t width, uint32_t height, const std::string& windowTitle);
	};


} // Lambix
