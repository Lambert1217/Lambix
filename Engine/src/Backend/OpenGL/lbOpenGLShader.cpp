/**
 ***************************************************************
 * @file            : lbOpenGLShader.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/24
 ***************************************************************
 */
//

#include "Backend/OpenGL/lbOpenGLShader.h"
#include "Log/lbLog.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Lambix
{
	// lbOpenGLShader
	lbOpenGLShader::lbOpenGLShader(lbShaderType type) : m_Type(type), m_RendererID(0)
	{
	}
	lbOpenGLShader::~lbOpenGLShader()
	{
		if(m_RendererID != 0){
			glDeleteShader(m_RendererID);
		}
	}
	void lbOpenGLShader::CompileFromSource(const std::string& source)
	{
		// 判断是否已经存在
		if(m_RendererID != 0){
			glDeleteShader(m_RendererID);
		}
		// 根据着色器类型创建并编译着色器
		GLenum glShaderType;
		switch (m_Type) {
		case lbShaderType::Vertex:
			glShaderType = GL_VERTEX_SHADER;
			break;
		case lbShaderType::Fragment:
			glShaderType = GL_FRAGMENT_SHADER;
			break;
		default:
			LOG_ASSERT(false, "Unsupported shader type");
			return;
		}
		// 创建着色器
		m_RendererID = glCreateShader(glShaderType);
		const GLchar* shaderSource = source.c_str();
		glShaderSource(m_RendererID, 1, &shaderSource, nullptr);
		glCompileShader(m_RendererID);
		// 检查编译状态
		GLint success;
		glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(m_RendererID, 512, nullptr, infoLog);
			LOG_ERROR("ERROR::SHADER::COMPILATION_FAILED\n");
			glDeleteShader(m_RendererID);
			LOG_ASSERT(false, infoLog);
		}
	}
	void lbOpenGLShader::CompileFromFile(const std::string& filepath)
	{
		// 从文件读取程序
		std::string source;
		try
		{
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			shaderFile.open(filepath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			source = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			LOG_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
			LOG_ASSERT(false, e.what());
		}
		// 编译
		CompileFromSource(source);
	}
	lbShaderType lbOpenGLShader::GetType() const
	{
		return m_Type;
	}
	uint32_t lbOpenGLShader::GetID() const
	{
		return m_RendererID;
	}
	// lbOpenGLShaderProgram
	lbOpenGLShaderProgram::lbOpenGLShaderProgram() : m_RendererID(0)
	{
	}
	lbOpenGLShaderProgram::~lbOpenGLShaderProgram()
	{
		if (m_RendererID != 0) {
			glDeleteProgram(m_RendererID);
		}
	}
	void lbOpenGLShaderProgram::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void lbOpenGLShaderProgram::Unbind() const
	{
		glUseProgram(0);
	}
	void lbOpenGLShaderProgram::BindUniformBlock(const std::string &blockName, uint32_t bindingPoint) const
	{
		GLuint index = glGetUniformBlockIndex(m_RendererID, blockName.c_str());
		if (index != GL_INVALID_INDEX)
		{
			glUniformBlockBinding(m_RendererID, index, bindingPoint);
		}
	}
	bool lbOpenGLShaderProgram::Link(const std::shared_ptr<lbShader>& vertexShader,
		const std::shared_ptr<lbShader>& fragmentShader)
	{
		if(m_RendererID != 0){
			glDeleteProgram(m_RendererID);
		}
		if(vertexShader->GetType() != lbShaderType::Vertex || fragmentShader->GetType() != lbShaderType::Fragment)
		{
			LOG_ERROR("ERROR::SHADER::LINK::Wrong shader type!");
			return false;
		}
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader->GetID());
		glAttachShader(m_RendererID, fragmentShader->GetID());
		glLinkProgram(m_RendererID);
		// 检查链接状态
		GLint success;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
			LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
			return false;
		}
		return true;
	}
	void lbOpenGLShaderProgram::UploadUniformInt(const std::string& name, const int value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void lbOpenGLShaderProgram::UploadUniformFloat(const std::string& name, const float value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void lbOpenGLShaderProgram::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	void lbOpenGLShaderProgram::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void lbOpenGLShaderProgram::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void lbOpenGLShaderProgram::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
} // Lambix