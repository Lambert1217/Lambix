/**
 ***************************************************************
 * @file            : lbBuffer.h
 * @author          : Lambert
 * @brief           : 定义了用于图形渲染的缓冲区相关的类和结构体。
 * @attention       :
 * - 这个头文件包含了顶点缓冲区（Vertex Buffer）和索引缓冲区（Index Buffer）的抽象接口。
 * - 它还定义了用于描述缓冲区布局（Buffer Layout）的结构和类。
 * - 所有类都设计为抽象基类，以便于不同图形API（如OpenGL, DirectX等）的实现。
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{

	/**
	 * @enum lbShaderDataType
	 * @brief 枚举着色器数据类型
	 *
	 * 定义了各种在着色器中使用的基本数据类型。
	 */
	enum class lbShaderDataType
	{
		None = 0,     ///< 无类型
		Float,        ///< 单精度浮点数
		Float2,       ///< 包含两个单精度浮点数的向量
		Float3,       ///< 包含三个单精度浮点数的向量
		Float4,       ///< 包含四个单精度浮点数的向量
		Mat3,         ///< 3x3的矩阵
		Mat4,         ///< 4x4的矩阵
		Int,          ///< 整数
		Int2,         ///< 包含两个整数的向量
		Int3,         ///< 包含三个整数的向量
		Int4,         ///< 包含四个整数的向量
		Bool          ///< 布尔值
	};

	/**
	 * @brief 获取指定着色器数据类型的字节大小
	 * @param type 要查询的着色器数据类型
	 * @return 返回数据类型的字节大小
	 */
	static uint32_t ShaderDataTypeSize(lbShaderDataType type);

	/**
	 * @struct lbBufferElement
	 * @brief 描述单个缓冲区元素的结构
	 *
	 * 这个结构用于定义缓冲区中单个属性的信息，包括名称、类型、大小、偏移和是否标准化。
	 */
	struct lbBufferElement
	{
		std::string Name;       ///< 属性的名称
		lbShaderDataType Type;  ///< 属性的数据类型
		uint32_t Size;			///< 属性的字节大小
		bool Normalized;        ///< 是否需要将整数值转换为标准化浮点值
		uint32_t Index;			///< 属性的索引(对应着色器程序中的location)

		lbBufferElement() = default;

		/**
		 * @brief 构造函数
		 * @param name 属性的名称
		 * @param type 属性的数据类型
		 * @param normalized 是否需要标准化（默认为false）
		 */
		lbBufferElement(const std::string &name, lbShaderDataType type, uint32_t index, bool normalized = false);

		/**
		 * @brief 获取属性的组件数量
		 * @return 返回属性的组件数量（例如Float3有3个组件）
		 */
		[[nodiscard]] uint32_t GetComponentCount() const;
	};

	/**
	 * @class lbVertexBuffer
	 * @brief 顶点缓冲区的抽象接口
	 *
	 * 这个类提供了一套方法来管理顶点数据的缓冲区。
	 */
	class lbVertexBuffer
	{
	 public:
		virtual ~lbVertexBuffer() = default;

		virtual void Bind() const = 0;                ///< 绑定缓冲区
		virtual void Unbind() const = 0;              ///< 解绑缓冲区

		virtual const lbBufferElement &GetElement() const = 0; ///< 获取缓冲区元素

		virtual void *GetData() const = 0;		  ///< 获取缓冲区数据的指针
		virtual uint32_t GetDataSize() const = 0; ///< 获取缓冲区数据的大小

		/**
		 * @brief 创建一个新的顶点缓冲区
		 * @param vertices 顶点数据的指针
		 * @param size 顶点数据的总字节大小
		 * @return 返回指向新创建的顶点缓冲区的智能指针
		 */
		static std::shared_ptr<lbVertexBuffer> Create(void *data, uint32_t size, const lbBufferElement &element);
	};

	/**
	 * @class lbIndexBuffer
	 * @brief 索引缓冲区的抽象接口
	 *
	 * 这个类提供了一套方法来管理索引数据的缓冲区。
	 */
	class lbIndexBuffer
	{
	 public:
		virtual ~lbIndexBuffer() = default;

		virtual void Bind() const = 0;                ///< 绑定缓冲区
		virtual void Unbind() const = 0;              ///< 解绑缓冲区

		/**
		 * @brief 获取索引缓冲区中索引的数量
		 * @return 返回索引的数量
		 */
		[[nodiscard]] virtual uint32_t GetCount() const = 0;

		/**
		 * @brief 创建一个新的索引缓冲区
		 * @param indices 索引数据的指针
		 * @param count 索引的数量
		 * @return 返回指向新创建的索引缓冲区的智能指针
		 */
		static std::shared_ptr<lbIndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

} // Lambix
