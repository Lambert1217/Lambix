/**
 ***************************************************************
 * @file            : lbTexture.h
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/25
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{
	class lbTexture
	{
	 public:
		virtual ~lbTexture() = default;

		enum class lbTextureType
		{
			Texture2D,
			CubeMap,
			Texture2DArray,
			Texture3D
		};

		enum class WrapMode
		{
			Repeat,
			ClampToEdge,
			MirroredRepeat
		};
		enum class FilterMode
		{
			Nearest,
			Linear,
			LinearMipmapLinear
		};
		enum class Format
		{
			RGB,
			RGBA,
			Depth24Stencil8
		};

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(
			void *data,
			uint32_t width,
			uint32_t height,
			uint32_t xoffset = 0,
			uint32_t yoffset = 0,
			Format dataFormat = Format::RGBA) = 0;

		virtual void SetWrapMode(WrapMode s, WrapMode t, WrapMode r = WrapMode::Repeat) = 0;
		virtual void SetFilter(FilterMode minFilter, FilterMode magFilter) = 0;
		virtual void GenerateMipmaps() = 0;

		virtual bool IsMipmapped() const = 0;
		virtual Format GetInternalFormat() const = 0;

		static std::shared_ptr<lbTexture> Create(const std::string& path);
		static std::shared_ptr<lbTexture> Create(uint32_t width, uint32_t height);
		static std::shared_ptr<lbTexture> Create(lbTextureType type, uint32_t width, uint32_t height, Format format);

	protected:
		bool m_parametersDirty = true; // 参数变化标记
		bool m_dataDirty = false;	   // 数据更新标记
		bool m_mipmapsDirty = false;   // Mipmap状态
	};
}
