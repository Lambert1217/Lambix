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
		 * @brief 添加一个顶点缓冲区到VAO
		 * @param vertexBuffer 指向顶点缓冲区对象的智能指针
		 *
		 * 添加顶点缓冲区到当前的VAO中，VAO会存储顶点属性的配置信息。
		 */
		virtual void AddVertexBuffer(const std::shared_ptr<lbVertexBuffer>) = 0;

		/**
		 * @brief 设置VAO的索引缓冲区
		 * @param indexBuffer 指向索引缓冲区对象的智能指针
		 *
		 * 设置索引缓冲区，通常用于绘制索引三角形、线条等。
		 */
		virtual void SetIndexBuffer(const std::shared_ptr<lbIndexBuffer>) = 0;

		/**
		 * @brief 获取当前VAO中所有的顶点缓冲区
		 * @return 返回包含所有顶点缓冲区的const引用
		 *
		 * 这个方法用于获取VAO中存储的所有顶点缓冲区对象。
		 */
		[[nodiscard]] virtual const std::vector<std::shared_ptr<lbVertexBuffer>>& GetVertexBuffers() const = 0;

		/**
		 * @brief 获取VAO中的索引缓冲区
		 * @return 返回指向索引缓冲区的智能指针的const引用
		 *
		 * 获取当前VAO中设置的索引缓冲区对象。
		 */
		[[nodiscard]] virtual const std::shared_ptr<lbIndexBuffer>& GetIndexBuffer() const = 0;

		/**
		 * @brief 创建一个新的顶点数组对象
		 * @return 返回指向新创建的顶点数组对象的智能指针
		 *
		 * 这个静态方法用于创建一个新的VAO实例。
		 */
		static std::shared_ptr<lbVertexArray> Create();
	};

} // Lambix
