/**
 ***************************************************************
 * @file            : lbShader.h
 * @author          : Lambert
 * @brief           : 定义了着色器（Shader）和着色器程序（Shader Program）的抽象接口。
 * @attention       :
 * - 这个头文件定义了用于OpenGL的着色器和着色器程序的抽象基类。
 * - 着色器类（`lbShader`）负责单个着色器的编译和管理。
 * - 着色器程序类（`lbShaderProgram`）负责管理多个着色器的链接和使用。
 * @data            : 2024/11/24
 ***************************************************************
 */
//

#pragma once

#include "glm/glm.hpp"

namespace Lambix
{
	/**
	 * @enum lbShaderType
	 * @brief 枚举着色器类型
	 */
	enum class lbShaderType{
		Vertex = 0,   ///< 顶点着色器
		Fragment      ///< 片段着色器
	};

	/**
	 * @class lbShader
	 * @brief 定义了单个着色器的抽象接口
	 *
	 * 这个类提供了一套方法来编译和管理单个着色器，包括从源代码或文件编译着色器，
	 * 以及获取着色器的类型和ID。
	 */
	class lbShader {
	 public:
		virtual ~lbShader() = default;

		/**
		 * @brief 从字符串源码编译着色器
		 * @param source 包含着色器源代码的字符串
		 */
		virtual void CompileFromSource(const std::string &source) = 0;

		/**
		 * @brief 从文件中编译着色器
		 * @param filepath 着色器源文件的路径
		 */
		virtual void CompileFromFile(const std::string &filepath) = 0;

		/**
		 * @brief 获取当前着色器的类型
		 * @return 返回着色器类型（顶点或片段）
		 */
		[[nodiscard]] virtual lbShaderType GetType() const = 0;

		/**
		 * @brief 获取着色器的ID
		 * @return 返回着色器ID
		 */
		[[nodiscard]] virtual uint32_t GetID() const = 0;

		/**
		 * @brief 创建一个新的着色器实例
		 * @param type 要创建的着色器类型
		 * @return 返回指向新创建的着色器的智能指针
		 */
		static std::shared_ptr<lbShader> Create(lbShaderType type);
	};


	/**
	 * @class lbShaderProgram
	 * @brief 定义了着色器程序的抽象接口
	 *
	 * 这个类负责管理多个着色器的链接，形成一个完整的着色器程序。
	 * 它提供了绑定、解绑和链接着色器的方法。
	 */
	class lbShaderProgram
	{
	 public:
		virtual ~lbShaderProgram() = default;

		/**
		 * @brief 绑定当前着色器程序
		 */
		virtual void Bind() const = 0;

		/**
		 * @brief 解绑当前着色器程序
		 */
		virtual void Unbind() const = 0;

		virtual void BindUniformBlock(const std::string &blockName, uint32_t bindingPoint) const = 0;

		virtual void UploadUniformInt(const std::string& name, const int value) = 0;
		virtual void UploadUniformFloat(const std::string& name, const float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		/**
		 * @brief 链接顶点和片段着色器，创建一个着色器程序
		 * @param vertexShader 顶点着色器的智能指针
		 * @param fragmentShader 片段着色器的智能指针
		 * @return 如果链接成功返回true，否则返回false
		 *
		 * 这个方法负责将提供的顶点和片段着色器链接到一个着色器程序中。
		 * 它会检查链接是否成功，并在失败时可能输出错误信息。
		 */
		virtual bool Link(const std::shared_ptr<lbShader>& vertexShader, const std::shared_ptr<lbShader>& fragmentShader) = 0;

		/**
		 * @brief 创建一个新的着色器程序实例
		 * @return 返回指向新创建的着色器程序的智能指针
		 */
		static std::shared_ptr<lbShaderProgram> Create();
	};

} // Lambix
