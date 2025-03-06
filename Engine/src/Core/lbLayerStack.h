/**
 ***************************************************************
 * @file            lbLayerStack.h
 * @author          Lambert
 * @brief           该文件包含 lbLayerStack 类的定义。
 *                  lbLayerStack 类用于管理层的栈结构，
 *                  支持普通层和覆盖层的入栈和出栈操作。
 * @attention       无
 * @date            2024/8/21
 ***************************************************************
 */

#pragma once

#include "lbLayer.h"

namespace Lambix
{

	/**
	 * @class lbLayerStack
	 * @brief 管理层的栈结构。
	 *
	 * lbLayerStack 类用于管理层的栈结构，支持普通层和覆盖层的入栈和出栈操作。
	 * 普通层从栈的头部插入，覆盖层从栈的尾部插入。
	 */
	class lbLayerStack
	{
	 public:
		/**
		 * @brief 构造一个 lbLayerStack 实例。
		 */
		lbLayerStack();

		/**
		 * @brief 析构 lbLayerStack 实例。
		 */
		~lbLayerStack();

		/**
		 * @brief 将普通层推入栈中。
		 * @param layer 要推入栈中的普通层。
		 * 普通层从栈的头部插入。
		 */
		void PushLayer(lbLayer* layer);

		/**
		 * @brief 将覆盖层推入栈中。
		 * @param overlay 要推入栈中的覆盖层。
		 * 覆盖层从栈的尾部插入。
		 */
		void PushOverlay(lbLayer* overlay);

		/**
		 * @brief 从栈中弹出普通层。
		 * @param layer 要弹出的普通层。
		 */
		void PopLayer(lbLayer* layer);

		/**
		 * @brief 从栈中弹出覆盖层。
		 * @param overlay 要弹出的覆盖层。
		 */
		void PopOverlay(lbLayer* overlay);

		/**
		 * @brief 获取栈的开始迭代器，方便外部遍历。
		 * @return 层栈的开始迭代器。
		 */
		std::vector<lbLayer*>::iterator begin() { return m_Layers.begin(); }

		/**
		 * @brief 获取栈的结束迭代器，方便外部遍历。
		 * @return 层栈的结束迭代器。
		 */
		std::vector<lbLayer*>::iterator end() { return m_Layers.end(); }

	 private:
		std::vector<lbLayer*> m_Layers; ///< 存储层的向量。
		unsigned int m_LayerInsertIndex{ 0 }; ///< 指向普通层的最后一个位置。
	};

} // namespace Lambix
