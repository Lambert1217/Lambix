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

#include "Renderer/lbTexture.h"
#include "glad/glad.h"

namespace Lambix
{
	class lbOpenGLTexture : public lbTexture
	{
	public:
		lbOpenGLTexture(const std::string &path);
		lbOpenGLTexture(uint32_t width, uint32_t height);
		lbOpenGLTexture(lbTextureType type, uint32_t width, uint32_t height, Format format);

		~lbOpenGLTexture() override;

		void Bind(uint32_t slot) const override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		uint32_t GetRendererID() const override;

		void SetWrapMode(WrapMode s, WrapMode t, WrapMode r = WrapMode::Repeat) override;
		void SetFilter(FilterMode minFilter, FilterMode magFilter) override;
		void GenerateMipmaps() override;
		bool IsMipmapped() const override;
		Format GetInternalFormat() const override;

		void SetData(void *data, uint32_t width, uint32_t height,
					 uint32_t xoffset, uint32_t yoffset,
					 Format dataFormat) override;

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
		const std::string m_Path;
		GLenum m_Target; // 纹理类型标识
		bool m_MipmapsGenerated = false;

		// 转换帮助函数
		GLenum ConvertWrap(WrapMode mode) const;
		GLenum ConvertFilter(FilterMode mode) const;
		GLenum ConvertFormat(Format format) const;
	};
}