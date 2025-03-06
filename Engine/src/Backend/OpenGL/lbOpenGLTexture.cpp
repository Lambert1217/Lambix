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

#include "Backend/OpenGL/lbOpenGLTexture.h"
#include "Log/lbLog.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Lambix
{
	lbOpenGLTexture::lbOpenGLTexture(const std::string& path) : m_Path(path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LOG_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		LOG_ASSERT(internalFormat & dataFormat, "Format is not supported!");

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		m_Target = GL_TEXTURE_2D;

		glCreateTextures(m_Target, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		// 设置默认参数
		SetFilter(FilterMode::Linear, FilterMode::Nearest);
		SetWrapMode(WrapMode::Repeat, WrapMode::Repeat);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	lbOpenGLTexture::lbOpenGLTexture(uint32_t width, uint32_t height)
		: lbOpenGLTexture(lbTextureType::Texture2D, width, height, Format::RGBA) {}

	lbOpenGLTexture::lbOpenGLTexture(lbTextureType type, uint32_t width, uint32_t height, Format format)
		: m_Width(width), m_Height(height)
	{
		// 完整类型处理
		switch (type)
		{
		case lbTextureType::Texture2D:
			m_Target = GL_TEXTURE_2D;
			break;
		case lbTextureType::CubeMap:
			m_Target = GL_TEXTURE_CUBE_MAP;
			break;
		case lbTextureType::Texture2DArray:
			m_Target = GL_TEXTURE_2D_ARRAY;
			break;
		case lbTextureType::Texture3D:
			m_Target = GL_TEXTURE_3D;
			break;
		default:
			LOG_ERROR("Unsupported texture type: {}", static_cast<int>(type));
			LOG_ASSERT(false, "See above for error details");
		}

		// 格式转换
		m_InternalFormat = ConvertFormat(format);

		// 创建纹理存储
		glCreateTextures(m_Target, 1, &m_RendererID);

		// 根据类型初始化存储
		if (m_Target == GL_TEXTURE_3D)
		{
			glTextureStorage3D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height, 1); // 默认depth=1
		}
		else
		{
			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		}

		// 设置默认参数
		SetFilter(FilterMode::Linear, FilterMode::Nearest);
		SetWrapMode(WrapMode::Repeat, WrapMode::Repeat, WrapMode::Repeat);
	}
	lbOpenGLTexture::~lbOpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void lbOpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	uint32_t lbOpenGLTexture::GetWidth() const
	{
		return m_Width;
	}
	uint32_t lbOpenGLTexture::GetHeight() const
	{
		return m_Height;
	}
	uint32_t lbOpenGLTexture::GetRendererID() const
	{
		return m_RendererID;
	}

	// 转换函数实现
	GLenum lbOpenGLTexture::ConvertWrap(WrapMode mode) const
	{
		switch (mode)
		{
		case WrapMode::Repeat:
			return GL_REPEAT;
		case WrapMode::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
		case WrapMode::MirroredRepeat:
			return GL_MIRRORED_REPEAT;
		default:
			LOG_ASSERT(false, "Unknown wrap mode!");
		}
		return GL_REPEAT;
	}

	GLenum lbOpenGLTexture::ConvertFilter(FilterMode mode) const
	{
		switch (mode)
		{
		case FilterMode::Nearest:
			return GL_NEAREST;
		case FilterMode::Linear:
			return GL_LINEAR;
		case FilterMode::LinearMipmapLinear:
			return GL_LINEAR_MIPMAP_LINEAR;
		default:
			LOG_ASSERT(false, "Unknown filter mode!");
		}
		return GL_LINEAR;
	}

	GLenum lbOpenGLTexture::ConvertFormat(Format format) const
	{
		switch (format)
		{
		case Format::RGB:
			return GL_RGB8;
		case Format::RGBA:
			return GL_RGBA8;
		case Format::Depth24Stencil8:
			return GL_DEPTH24_STENCIL8;
		default:
			LOG_ASSERT(false, "Unsupported texture format!");
		}
		return GL_RGBA8;
	}

	// 包装模式设置
	void lbOpenGLTexture::SetWrapMode(WrapMode s, WrapMode t, WrapMode r)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, ConvertWrap(s));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, ConvertWrap(t));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_R, ConvertWrap(r));
		m_parametersDirty = false;
	}

	// 过滤模式设置
	void lbOpenGLTexture::SetFilter(FilterMode minFilter, FilterMode magFilter)
	{
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, ConvertFilter(minFilter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, ConvertFilter(magFilter));
		m_parametersDirty = false;
	}

	// Mipmap生成
	void lbOpenGLTexture::GenerateMipmaps()
	{
		if (!m_MipmapsGenerated)
		{
			glGenerateTextureMipmap(m_RendererID);
			m_MipmapsGenerated = true;
			m_mipmapsDirty = false;
		}
	}

	// 局部数据更新
	void lbOpenGLTexture::SetData(void *data, uint32_t width, uint32_t height,
								  uint32_t xoffset, uint32_t yoffset, Format dataFormat)
	{
		switch (dataFormat)
		{
		case Format::RGB:
			m_DataFormat = GL_RGB;
			break;
		case Format::RGBA:
			m_DataFormat = GL_RGBA;
			break;
		default:
			LOG_ASSERT(false, "Unsupported data format!");
		}

		glTextureSubImage2D(m_RendererID, 0, xoffset, yoffset,
							width, height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		m_dataDirty = false;
	}

	// 其他必要实现
	bool lbOpenGLTexture::IsMipmapped() const { return m_MipmapsGenerated; }
	lbTexture::Format lbOpenGLTexture::GetInternalFormat() const
	{
		switch (m_InternalFormat)
		{
		case GL_RGB8:
			return Format::RGB;
		case GL_RGBA8:
			return Format::RGBA;
		case GL_DEPTH24_STENCIL8:
			return Format::Depth24Stencil8;
		default:
			return Format::RGBA;
		}
	}
}
