/**
 ***************************************************************
 * @file            KeyEvent.h
 * @author          Lambert
 * @brief           该文件包含键盘事件的定义，包括键盘按下、释放和输入事件。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include "Event.h"

namespace Lambix
{

	/**
	 * @class KeyEvent
	 * @brief 键盘事件基类
	 *
	 * KeyEvent 类是所有键盘事件的基类，包含键码和相关的事件类别。
	 */
	class KeyEvent : public Event
	{
	 public:
		/**
		 * @brief 获取键码
		 * @return 键码
		 */
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	 protected:
		/**
		 * @brief 构造键盘事件
		 * @param keycode 键码
		 */
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode; ///< 键码
	};

	/**
	 * @class KeyPressedEvent
	 * @brief 键盘按下事件
	 *
	 * KeyPressedEvent 类表示键盘按下事件，包含键码和重复按下次数。
	 */
	class KeyPressedEvent : public KeyEvent
	{
	 public:
		/**
		 * @brief 构造键盘按下事件
		 * @param keycode 键码
		 * @param repeatCount 重复按下次数
		 */
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		/**
		 * @brief 获取重复按下次数
		 * @return 重复按下次数
		 */
		inline int GetRepeatCount() const { return m_RepeatCount; }

		/**
		 * @brief 返回事件信息
		 * @return 包含键码和重复次数的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	 private:
		int m_RepeatCount; ///< 重复按下次数
	};

	/**
	 * @class KeyReleasedEvent
	 * @brief 键盘释放事件
	 *
	 * KeyReleasedEvent 类表示键盘释放事件，包含键码。
	 */
	class KeyReleasedEvent : public KeyEvent
	{
	 public:
		/**
		 * @brief 构造键盘释放事件
		 * @param keycode 键码
		 */
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		/**
		 * @brief 返回事件信息
		 * @return 包含键码的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/**
	 * @class KeyTypedEvent
	 * @brief 键盘输入事件
	 *
	 * KeyTypedEvent 类表示键盘输入事件，包含键码。
	 */
	class KeyTypedEvent : public KeyEvent
	{
	 public:
		/**
		 * @brief 构造键盘输入事件
		 * @param keycode 键码
		 */
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		/**
		 * @brief 返回事件信息
		 * @return 包含键码的事件信息字符串
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
