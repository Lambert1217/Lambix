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
#include "Renderer/Interfaces/lbTexture.h"
#include "glad/glad.h"

namespace Lambix
{
	static GLenum ToGL(lbTextureWrapping wrap);
	static GLenum ToGL(lbTextureFilter filter);
	static GLenum ToGLFormat(lbTextureFormat format);
	static GLenum ToGLInternalFormat(lbTextureFormat format);

	class lbOpenGLTexture2D : public lbTexture2D
	{
	public:
		lbOpenGLTexture2D(const lbSource::Ptr &source, const lbTextureSpecification &spec);
		virtual ~lbOpenGLTexture2D() override;

		void Bind(uint32_t slot = 0) const override;
		void Unbind() const override;

		const lbTextureSpecification &GetSpecification() const override { return m_Spec; }
		uint32_t GetWidth() const override { return m_Source->mWidth; }
		uint32_t GetHeight() const override { return m_Source->mHeight; }
		lbTextureType GetTextureType() const override { return lbTextureType::Texture2D; }

	private:
		GLuint m_RendererID;
		lbSource::Ptr m_Source{nullptr};
		lbTextureSpecification m_Spec;
	};

	class lbOpenGLTextureCube : public lbTextureCube
	{
	public:
		lbOpenGLTextureCube(const std::array<lbSource::Ptr, 6> &sources, const lbTextureSpecification &spec);
		virtual ~lbOpenGLTextureCube() override;

		void Bind(uint32_t slot = 0) const override;
		void Unbind() const override;

		const lbTextureSpecification &GetSpecification() const override { return m_Spec; }
		uint32_t GetWidth() const override { return m_Sources[0]->mWidth; }
		uint32_t GetHeight() const override { return m_Sources[0]->mHeight; }
		lbTextureType GetTextureType() const override { return lbTextureType::TextureCubeMap; }

	private:
		GLuint m_RendererID;
		std::array<lbSource::Ptr, 6> m_Sources{nullptr};
		lbTextureSpecification m_Spec;
	};
}
