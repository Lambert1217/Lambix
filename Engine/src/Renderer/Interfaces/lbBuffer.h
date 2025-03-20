/**
 ***************************************************************
 * @file            : lbBuffer.h
 * @author          : Lambert
 * @brief           : 定义了用于图形渲染的缓冲区相关的类和结构体。
 * @attention       :
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Core/lbCore.h"

namespace Lambix
{
	/**
	 * @brief buffer规格描述
	 *
	 */
	struct lbBufferSpecification
	{
		lbBufferType bufferType;
		lbBufferAllocType bufferAllocType;
		lbDataType dataType;
	};

	/**
	 * @brief vbo/ebo 基类， 具体是哪一种从传入的规格规定
	 *
	 */
	class lbBuffer
	{
	public:
		virtual ~lbBuffer() = default;

		/**
		 * @brief 绑定buffer
		 *
		 */
		virtual void Bind() const = 0;

		/**
		 * @brief 解绑buffer
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 * @brief Set the Sub Data object
		 *
		 * @param data 数据
		 * @param range 更新的范围，单位是数据类型的大小
		 */
		virtual void SetSubData(const void *data, const lbRange &range) = 0;

		/**
		 * @brief Set the Data object
		 *
		 * @param data 数据
		 * @param size 数据大小，单位是数据类型的大小
		 */
		virtual void SetData(const void *data, uint32_t size) = 0;

		using Ptr = std::shared_ptr<lbBuffer>;
		static Ptr Create(const lbBufferSpecification &spec);
	};
} // Lambix
