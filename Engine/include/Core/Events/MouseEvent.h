/**
 ***************************************************************
 * @file            MouseEvent.h
 * @author          Lambert
 * @brief           该文件包含鼠标事件的定义，包括鼠标移动、滚轮滚动和鼠标按钮事件。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include "Event.h"

namespace Lambix
{

	/**
	 * @class MouseMovedEvent
	 * @brief 鼠标移动事件
	 *
	 * MouseMovedEvent 类表示鼠标移动事件，包含鼠标的新坐标。
	 */
	class MouseMovedEvent : public Event
	{
	 public:
		/**
		 * @brief 构造鼠标移动事件
		 * @param x 鼠标的新 X 坐标
		 * @param y 鼠标的新 Y 坐标
		 */
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		/**
		 * @brief 获取鼠标 X 坐标
		 * @return 鼠标的 X 坐标
		 */
		inline float GetX() const { return m_MouseX; }

		/**
		 * @brief 获取鼠标 Y 坐标
		 * @return 鼠标的 Y 坐标
		 */
		inline float GetY() const { return m_MouseY; }

		/**
		 * @brief 返回事件信息
		 * @return 包含鼠标坐标的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	 private:
		float m_MouseX; ///< 鼠标 X 坐标
		float m_MouseY; ///< 鼠标 Y 坐标
	};

	/**
	 * @class MouseScrolledEvent
	 * @brief 鼠标滚轮事件
	 *
	 * MouseScrolledEvent 类表示鼠标滚轮滚动事件，包含 X 和 Y 方向的滚动偏移量。
	 */
	class MouseScrolledEvent : public Event
	{
	 public:
		/**
		 * @brief 构造鼠标滚轮事件
		 * @param xOffset X 方向的滚动偏移量
		 * @param yOffset Y 方向的滚动偏移量
		 */
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		/**
		 * @brief 获取 X 方向的滚动偏移量
		 * @return X 方向的滚动偏移量
		 */
		inline float GetXOffset() const { return m_XOffset; }

		/**
		 * @brief 获取 Y 方向的滚动偏移量
		 * @return Y 方向的滚动偏移量
		 */
		inline float GetYOffset() const { return m_YOffset; }

		/**
		 * @brief 返回事件信息
		 * @return 包含滚动偏移量的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	 private:
		float m_XOffset; ///< X 方向的滚动偏移量
		float m_YOffset; ///< Y 方向的滚动偏移量
	};

	/**
	 * @class MouseButtonEvent
	 * @brief 鼠标按钮事件基类
	 *
	 * MouseButtonEvent 类是所有鼠标按钮事件的基类，包含鼠标按钮的编号。
	 */
	class MouseButtonEvent : public Event
	{
	 public:
		/**
		 * @brief 获取鼠标按钮编号
		 * @return 鼠标按钮编号
		 */
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	 protected:
		/**
		 * @brief 构造鼠标按钮事件
		 * @param button 鼠标按钮编号
		 */
		MouseButtonEvent(int button) : m_Button(button) {}

		int m_Button; ///< 鼠标按钮编号
	};

	/**
	 * @class MouseButtonPressedEvent
	 * @brief 鼠标按钮按下事件
	 *
	 * MouseButtonPressedEvent 类表示鼠标按钮按下事件，包含鼠标按钮编号。
	 */
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	 public:
		/**
		 * @brief 构造鼠标按钮按下事件
		 * @param button 鼠标按钮编号
		 */
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		/**
		 * @brief 返回事件信息
		 * @return 包含鼠标按钮编号的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/**
	 * @class MouseButtonReleasedEvent
	 * @brief 鼠标按钮释放事件
	 *
	 * MouseButtonReleasedEvent 类表示鼠标按钮释放事件，包含鼠标按钮编号。
	 */
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	 public:
		/**
		 * @brief 构造鼠标按钮释放事件
		 * @param button 鼠标按钮编号
		 */
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		/**
		 * @brief 返回事件信息
		 * @return 包含鼠标按钮编号的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
