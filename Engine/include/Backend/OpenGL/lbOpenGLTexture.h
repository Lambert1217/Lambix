/**
 ***************************************************************
 * @file            : lbOpenGLTexture.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#pragma once

#include "Core/Renderer/lbTexture.h"
#include "glad/glad.h"

namespace Lambix
{
	class lbOpenGLTexture : public lbTexture
	{
	 public:
		lbOpenGLTexture(const std::string& path);
		lbOpenGLTexture(uint32_t width, uint32_t height);
		~lbOpenGLTexture() override;

		void Bind(uint32_t slot) const override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		void SetData(void* data, uint32_t size) override;
	 private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
		const std::string m_Path;
	};
}