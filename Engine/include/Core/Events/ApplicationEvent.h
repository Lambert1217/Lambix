/**
 ***************************************************************
 * @file            ApplicationEvent.h
 * @author          Lambert
 * @brief           该文件包含应用程序事件的定义，包括窗口大小变化、窗口关闭、
 *                  应用程序滴答、更新和渲染事件。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include "Event.h"

namespace Lambix
{

	/**
	 * @class WindowResizeEvent
	 * @brief 窗口大小变化事件
	 *
	 * WindowResizeEvent 类表示窗口大小变化事件，包含窗口的新宽度和高度。
	 */
	class WindowResizeEvent : public Event
	{
	 public:
		/**
		 * @brief 构造窗口大小变化事件
		 * @param width 窗口的新宽度
		 * @param height 窗口的新高度
		 */
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		/**
		 * @brief 获取窗口宽度
		 * @return 窗口的宽度
		 */
		inline unsigned int GetWidth() const { return m_Width; }

		/**
		 * @brief 获取窗口高度
		 * @return 窗口的高度
		 */
		inline unsigned int GetHeight() const { return m_Height; }

		/**
		 * @brief 返回事件信息
		 * @return 包含窗口宽度和高度的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}

		// 利用宏生成一系列函数
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	 private:
		unsigned int m_Width;  ///< 窗口宽度
		unsigned int m_Height; ///< 窗口高度
	};

	/**
	 * @class WindowCloseEvent
	 * @brief 窗口关闭事件
	 *
	 * WindowCloseEvent 类表示窗口关闭事件。
	 */
	class WindowCloseEvent : public Event
	{
	 public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class AppTickEvent
	 * @brief 应用程序Tick事件
	 *
	 * AppTickEvent 类表示应用程序的Tick事件，通常用于应用程序的主循环。
	 */
	class AppTickEvent : public Event
	{
	 public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class AppUpdateEvent
	 * @brief 应用程序更新事件
	 *
	 * AppUpdateEvent 类表示应用程序的更新事件，通常用于处理应用程序的更新逻辑。
	 */
	class AppUpdateEvent : public Event
	{
	 public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @class AppRenderEvent
	 * @brief 应用程序渲染事件
	 *
	 * AppRenderEvent 类表示应用程序的渲染事件，通常用于处理应用程序的渲染逻辑。
	 */
	class AppRenderEvent : public Event
	{
	 public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
