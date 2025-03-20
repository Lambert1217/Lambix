/**
 ***************************************************************
 * @file            : lbOpenGLShader.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/24
 ***************************************************************
 */
//

#pragma once

#include "Renderer/Interfaces/lbShader.h"

namespace Lambix
{
	class lbOpenGLShader : public lbShader
	{
	public:
		lbOpenGLShader(lbShaderType type);
		~lbOpenGLShader() override;

		void CompileFromSource(const std::string &source) override;
		void CompileFromFile(const std::filesystem::path &filepath) override;

		lbShaderType GetType() const override;
		uint32_t GetID() const override;

	private:
		lbShaderType m_Type;
		uint32_t m_RendererID;
	};

	class lbOpenGLShaderProgram : public lbShaderProgram
	{
		friend class lbCache;

	public:
		lbOpenGLShaderProgram();
		~lbOpenGLShaderProgram() override;

		void Bind() const override;
		void Unbind() const override;
		void BindUniformBlock(const std::string &blockName, uint32_t bindingPoint) const override;
		bool Link(const std::shared_ptr<lbShader> &vertexShader, const std::shared_ptr<lbShader> &fragmentShader) override;

		void UploadUniformInt(const std::string &name, const int value) override;
		void UploadUniformFloat(const std::string &name, const float value) override;
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &value) override;
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &value) override;
		void UploadUniformFloat4(const std::string &name, const glm::vec4 &value) override;
		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) override;

		uint32_t &GetRefCount() override { return m_RefCount; }
		size_t &GetHashCode() override { return m_HashCode; }

	private:
		uint32_t m_RendererID{0};
		uint32_t m_RefCount{0};
		size_t m_HashCode{0};
	};

} // Lambix
