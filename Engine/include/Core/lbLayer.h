/**
 ***************************************************************
 * @file            lbLayer.h
 * @author          Lambert
 * @brief           该文件包含 lbLayer 类的定义。
 *                  lbLayer 类表示系统中的一个层，
 *                  可以进行附加、分离、更新和渲染操作。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include <utility>

#include "lbTimestep.h"
#include "Events/Event.h"

namespace Lambix
{
	/**
	 * @class lbLayer
	 * @brief 表示系统中的一个层。
	 *
	 * lbLayer 类作为不同层的基类，可以附加到系统中，
	 * 进行更新、渲染，并处理事件。它提供了这些操作的虚方法，
	 * 可以在派生类中重写这些方法。
	 */
	class lbLayer
	{
	 public:
		/**
		 * @brief 构造一个 lbLayer 实例，带有可选的名称。
		 * @param name 层的名称，默认为 "Layer"。
		 */
		explicit lbLayer(std::string  name = "Layer"): m_DebugName(std::move(name)) {}

		/**
		 * @brief 析构 lbLayer 实例。
		 */
		virtual ~lbLayer() = default;

		/**
		 * @brief 当层被附加时调用。
		 * 该方法可以被重写，以执行初始化任务。
		 */
		virtual void OnAttach() {}

		/**
		 * @brief 当层被分离时调用。
		 * 该方法可以被重写，以执行清理任务。
		 */
		virtual void OnDetach() {}

		/**
		 * @brief 每帧更新时调用。
		 * 该方法可以被重写，以执行更新任务。
		 * @param ts 时间步长，用于更新的时间信息。
		 */
		virtual void OnUpdate(lbTimestep ts) {}

		/**
		 * @brief 在 ImGui 渲染时调用。
		 * 该方法可以被重写，以在 ImGui 界面上渲染层的内容。
		 */
		virtual void OnImGuiRender() {}

		/**
		 * @brief 处理事件时调用。
		 * 该方法可以被重写，以响应各种事件。
		 * @param event 事件对象，包含事件的信息。
		 */
		virtual void OnEvent(Event& event) {}

		/**
		 * @brief 获取层的名称。
		 * @return 层的名称。
		 */
		inline const std::string& GetName() const { return m_DebugName; }

	 protected:
		std::string m_DebugName; ///< 层的名称，用于调试。
	};
}
