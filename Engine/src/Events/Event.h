/**
 ***************************************************************
 * @file            Event.h
 * @author          Lambert
 * @brief           事件基类，目前的事件系统仍是立即执行，即事件触发后立即处理。
 *                  未来可能会实现事件缓冲。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include "Core/lbCore.h"

namespace Lambix
{
	/**
	 * @brief 枚举事件类型
	 *
	 * 事件类型列举了系统中可能发生的各种事件。
	 */
	enum class EventType
	{
		None = 0,			 ///< 无事件
		WindowClose,		 ///< 窗口关闭事件
		WindowResize,		 ///< 窗口大小调整事件
		WindowFocus,		 ///< 窗口获得焦点事件
		WindowLostFocus,	 ///< 窗口失去焦点事件
		WindowMoved,		 ///< 窗口移动事件
		AppTick,			 ///< 应用程序Tick事件
		AppUpdate,			 ///< 应用程序更新事件
		AppRender,			 ///< 应用程序渲染事件
		KeyPressed,			 ///< 键盘按下事件
		KeyReleased,		 ///< 键盘释放事件
		KeyTyped,			 ///< 键盘输入事件
		MouseButtonPressed,	 ///< 鼠标按钮按下事件
		MouseButtonReleased, ///< 鼠标按钮释放事件
		MouseMoved,			 ///< 鼠标移动事件
		MouseScrolled		 ///< 鼠标滚动事件
	};

	/**
	 * @brief 枚举事件大类
	 *
	 * 事件大类用于事件的分类，可以用于事件过滤。
	 */
	enum EventCategory
	{
		None = 0,						   ///< 无事件大类
		EventCategoryApplication = BIT(0), ///< 应用程序事件
		EventCategoryInput = BIT(1),	   ///< 输入事件
		EventCategoryKeyboard = BIT(2),	   ///< 键盘事件
		EventCategoryMouse = BIT(3),	   ///< 鼠标事件
										   // EventCategoryMouseButton = BIT(4) ///< 鼠标按钮事件（注释掉的代码）
	};

	// 定义宏用于批量生成派生类中的重复性函数
#define EVENT_CLASS_TYPE(type)                                                  \
	static EventType GetStaticType() { return EventType::type; }                \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

	/**
	 * @class Event
	 * @brief 事件基类
	 *
	 * Event 类作为所有事件的基类，定义了事件的基本接口，包括获取事件类型、名称、
	 * 类别标志等方法。该类支持事件的基本操作，并提供了判断事件是否属于特定类别的方法。
	 */
	class Event
	{
		// 友元类，事件调度器
		friend class EventDispatcher;

	public:
		/**
		 * @brief 返回事件类型
		 * @return 事件的类型
		 */
		virtual EventType GetEventType() const = 0;

		/**
		 * @brief 返回事件名称
		 * @return 事件的名称
		 */
		virtual const char *GetName() const = 0;

		/**
		 * @brief 返回事件类别标志
		 * @return 事件的类别标志
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 * @brief 将事件名称转换为字符串
		 * @return 事件名称的字符串表示
		 */
		virtual std::string ToString() const { return GetName(); }

		/**
		 * @brief 判断事件是否属于指定的类别
		 * @param category 要检查的事件类别
		 * @return 如果事件属于指定类别，则返回 true；否则返回 false。
		 */
		inline bool IsInCategory(EventCategory category)
		{
			// 通过与运算判断事件是否属于指定类别
			return GetCategoryFlags() & category;
		}

		/**
		 * @brief 获取事件是否已被处理
		 * @return 如果事件已被处理，则返回 true；否则返回 false。
		 */
		inline bool GetHandled() { return Handled; }

	protected:
		bool Handled = false; ///< 事件是否已被处理
	};

	/**
	 * @brief 重载 << 操作符，输出事件信息
	 * @param os 输出流
	 * @param e 事件对象
	 * @return 输出流
	 */
	inline std::ostream &operator<<(std::ostream &os, const Event &e)
	{
		return os << e.ToString();
	}

	/**
	 * @class EventDispatcher
	 * @brief 事件调度器类
	 *
	 * EventDispatcher 类用于分发事件到处理函数。它支持根据事件类型将事件传递给
	 * 相应的处理函数，并记录事件是否已被处理。
	 */
	class EventDispatcher
	{
		template <typename T>
		using EventFun = std::function<bool(T &)>;

	public:
		/**
		 * @brief 构造事件调度器
		 * @param event 要调度的事件
		 */
		EventDispatcher(Event &event) : m_Event(event) {}

		/**
		 * @brief 分发事件到处理函数
		 * @param func 处理函数
		 * @return 如果事件被处理，则返回 true；否则返回 false。
		 */
		template <typename T>
		bool Dispatch(EventFun<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T *)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event &m_Event; ///< 要调度的事件
	};

} // namespace Lambix
