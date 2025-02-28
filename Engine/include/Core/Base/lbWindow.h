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
		 * @brief 窗口更新
		 */
		virtual void OnUpdate() = 0;

		/**
		 * @brief 设置垂直同步
		 * @param enabled
		 */
		virtual void SetVSync(bool enabled) = 0;

		/**
		 * @brief 返还当前是否垂直同步
		 * @return
		 */
		virtual bool IsVSync() const = 0;

		/**
		 * @brief 获取窗口宽度
		 * @return
		 */
		virtual uint32_t GetWidth() const = 0;

		/**
		 * @brief 获取窗口宽度
		 * @return
		 */
		virtual uint32_t GetHeight() const = 0;

		/**
		 * @brief 获取活动窗口
		 * @return
		 */
		[[nodiscard]] virtual void *GetNativeWindow() const = 0;

		/**
		 * @brief 设置开启最大化
		 *
		 */
		virtual void SetMaximized() = 0;

		/**
		 * @brief 窗口创建
		 */
		static lbWindow* Create(uint32_t width, uint32_t height, const std::string& windowTitle);
	};


} // Lambix
