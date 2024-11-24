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

#include "Core/Renderer/lbShader.h"

namespace Lambix
{

	class lbOpenGLShader : public lbShader
	{
	 public:
		lbOpenGLShader(lbShaderType type);
		~lbOpenGLShader() override;

		void CompileFromSource(const std::string& source) override;
		void CompileFromFile(const std::string& filepath) override;

		lbShaderType GetType() const override;
		uint32_t GetID() const override;
	 private:
		lbShaderType m_Type;
		uint32_t m_RendererID;
	};

	class lbOpenGLShaderProgram : public lbShaderProgram
	{
	 public:
		lbOpenGLShaderProgram();
		~lbOpenGLShaderProgram() override;

		void Bind() const override;
		void Unbind() const override;
		bool Link(const std::shared_ptr<lbShader>& vertexShader, const std::shared_ptr<lbShader>& fragmentShader) override;
	 private:
		uint32_t m_RendererID;
	};

} // Lambix
