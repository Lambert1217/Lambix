/**
 ***************************************************************
 * @file            : lbOpenGLTexture.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#include "Log/lbLog.h"
#include "Resource/lbCache.h"
#include "Events/lbEventPool.h"
#include "lbOpenGLTexture.h"

namespace Lambix
{
	// OpenGL 格式转换
	static GLenum ToGL(lbTextureWrapping wrap)
	{
		switch (wrap)
		{
		case lbTextureWrapping::RepeatWrapping:
			return GL_REPEAT;
		case lbTextureWrapping::ClampToEdgeWrapping:
			return GL_CLAMP_TO_EDGE;
		case lbTextureWrapping::ClampToBorder:
			return GL_CLAMP_TO_BORDER;
		case lbTextureWrapping::MirroredRepeatWrapping:
			return GL_MIRRORED_REPEAT;
		default:
			return GL_REPEAT;
		}
	}

	static GLenum ToGL(lbTextureFilter filter)
	{
		switch (filter)
		{
		case lbTextureFilter::LinearFilter:
			return GL_LINEAR;
		case lbTextureFilter::NearestFilter:
			return GL_NEAREST;
		default:
			return GL_LINEAR;
		}
	}

	static GLenum ToGLFormat(lbTextureFormat format)
	{
		switch (format)
		{
		case lbTextureFormat::RGB:
			return GL_RGB;
		case lbTextureFormat::RGBA:
			return GL_RGBA;
		case lbTextureFormat::DepthFormat:
			return GL_DEPTH_COMPONENT;
		case lbTextureFormat::DepthStencilFormat:
			return GL_DEPTH_STENCIL;
		default:
			return GL_RGBA;
		}
	}

	static GLenum ToGLInternalFormat(lbTextureFormat format)
	{
		switch (format)
		{
		case lbTextureFormat::RGB:
			return GL_RGB8;
		case lbTextureFormat::RGBA:
			return GL_RGBA8;
		case lbTextureFormat::DepthFormat:
			return GL_DEPTH_COMPONENT24;
		case lbTextureFormat::DepthStencilFormat:
			return GL_DEPTH24_STENCIL8;
		default:
			return GL_RGBA8;
		}
	}

	// 2D 纹理实现
	lbOpenGLTexture2D::lbOpenGLTexture2D(const lbSource::Ptr &source, const lbTextureSpecification &spec)
		: m_Source(source), m_Spec(spec)
	{
		LOG_ASSERT(source->mWidth == spec.width && source->mHeight == spec.height, "Conflict between source and spec!");

		// 纹理创建
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		// 上传纹理数据
		const GLenum format = ToGLFormat(m_Spec.format);
		const GLenum internalFormat = ToGLInternalFormat(m_Spec.format);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Source->mWidth, m_Source->mHeight, 0, format, GL_UNSIGNED_BYTE, m_Source->mData.data());

		// 设置纹理参数
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, ToGL(m_Spec.minFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, ToGL(m_Spec.magFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, ToGL(m_Spec.wrapS));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, ToGL(m_Spec.wrapT));
	}

	lbOpenGLTexture2D::~lbOpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
		// 发出事件
		lbEvent::Ptr event = lbEventPool::Get()->Acquire();
		event->Set("SourceRelease", m_Source.get(), nullptr);
		lbEventDispatcher::Get()->dispatchEvent(event);
	}

	void lbOpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void lbOpenGLTexture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// 立方体贴图实现
	lbOpenGLTextureCube::lbOpenGLTextureCube(const std::array<lbSource::Ptr, 6> &sources, const lbTextureSpecification &spec)
		: m_Sources(sources), m_Spec(spec)
	{
		LOG_ASSERT(sources[0]->mWidth == spec.width && sources[0]->mHeight == spec.height, "Conflict between source and spec!");

		// 创建纹理
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

		// 上传数据
		const GLenum format = ToGLFormat(m_Spec.format);
		const GLenum internalFormat = ToGLInternalFormat(m_Spec.format);
		for (GLuint i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat,
						 m_Sources[i]->mWidth, m_Sources[i]->mHeight, 0,
						 format, GL_UNSIGNED_BYTE, m_Sources[i]->mData.data());
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, ToGL(m_Spec.minFilter));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, ToGL(m_Spec.magFilter));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, ToGL(m_Spec.wrapS));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, ToGL(m_Spec.wrapT));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, ToGL(m_Spec.wrapR));
	}

	lbOpenGLTextureCube::~lbOpenGLTextureCube()
	{
		glDeleteTextures(1, &m_RendererID);
		for (auto it : m_Sources)
		{
			// 发出事件
			lbEvent::Ptr event = lbEventPool::Get()->Acquire();
			event->Set("SourceRelease", it.get(), nullptr);
			lbEventDispatcher::Get()->dispatchEvent(event);
		}
	}

	void lbOpenGLTextureCube::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
	}

	void lbOpenGLTextureCube::Unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}
