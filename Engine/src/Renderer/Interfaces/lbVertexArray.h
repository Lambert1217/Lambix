/**
 ***************************************************************
 * @file            : lbVertexArray.h
 * @author          : Lambert
 * @brief           : 定义了顶点数组对象（Vertex Array Object, VAO）的抽象接口。
 * @attention       :
 * - 顶点数组对象是OpenGL中用于存储顶点缓冲区对象（VBO）和索引缓冲区对象（EBO）状态的对象。
 * - 它提供了简化的顶点属性配置和渲染流程。
 * - 本接口类设计为抽象基类，允许不同图形API的具体实现。
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "lbBuffer.h"

namespace Lambix
{

	/**
	 * @class lbVertexArray
	 * @brief 顶点数组对象（VAO）的抽象接口
	 *
	 * 这个类提供了一套方法来管理顶点数组对象，包括绑定、解绑、添加顶点缓冲区和设置索引缓冲区。
	 */
	class lbVertexArray
	{
	public:
		virtual ~lbVertexArray() = default;

		/**
		 * @brief 绑定当前顶点数组对象
		 *
		 * 这个方法将当前的VAO设置为活动状态，使得后续的OpenGL绘制操作使用此VAO的配置。
		 */
		virtual void Bind() const = 0;

		/**
		 * @brief 解绑当前顶点数组对象
		 *
		 * 这个方法将当前的VAO从活动状态中移除，使得OpenGL绘制操作不再使用此VAO。
		 */
		virtual void Unbind() const = 0;

		/**
		 * @brief
		 *
		 * @param binding 绑定槽位
		 * @param itemSize 单个数据的大小 例如：position 就是3
		 * @param type 数据类型
		 * @param normalized 是否规范化
		 * @param stride 指定连续通用顶点属性之间的字节偏移量。如果步幅 为 0，则通用顶点属性为 理解为紧密地包装在 数组
		 * @param pointer 第一个泛型顶点属性的第一个组件的偏移量
		 */
		virtual void lbVertexAttribPointer(uint32_t binding, uint32_t itemSize, const lbDataType &type, bool normalized, uint32_t stride, const void *pointer) = 0;

		/**
		 * @brief 创建一个新的顶点数组对象
		 * @return 返回指向新创建的顶点数组对象的智能指针
		 *
		 * 这个静态方法用于创建一个新的VAO实例。
		 */
		using Ptr = std::shared_ptr<lbVertexArray>;
		static Ptr Create();
	};

} // Lambix
