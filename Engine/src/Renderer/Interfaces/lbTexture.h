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

#include "Core/lbCore.h"
#include "Utils/lbSource.h"

namespace Lambix
{
	// 纹理规格描述
	struct lbTextureSpecification
	{
		// 大小
		uint32_t width{1}, height{1};
		// dataType
		lbDataType dataType{lbDataType::UnsignedByteType};
		// Warping
		lbTextureWrapping wrapS{lbTextureWrapping::RepeatWrapping};
		lbTextureWrapping wrapT{lbTextureWrapping::RepeatWrapping};
		lbTextureWrapping wrapR{lbTextureWrapping::RepeatWrapping};
		// Filter
		lbTextureFilter magFilter{lbTextureFilter::LinearFilter};
		lbTextureFilter minFilter{lbTextureFilter::NearestFilter};
		// format
		lbTextureFormat format{lbTextureFormat::RGBA};
		lbTextureFormat internalFormat{lbTextureFormat::RGBA};
	};

	// 纹理的基类
	class lbTexture
	{
	public:
		virtual ~lbTexture() = default;

		/**
		 * @brief 绑定到纹理槽位，默认为0
		 *
		 * @param slot
		 */
		virtual void Bind(uint32_t slot = 0) const = 0;

		/**
		 * @brief 取消纹理的绑定
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 * @brief Get the Specification object
		 *
		 * @return const lbTextureSpecification&
		 */
		virtual const lbTextureSpecification &GetSpecification() const = 0;

		/**
		 * @brief Get the Width
		 *
		 * @return uint32_t
		 */
		virtual uint32_t GetWidth() const = 0;

		/**
		 * @brief Get the Height
		 *
		 * @return uint32_t
		 */
		virtual uint32_t GetHeight() const = 0;

		/**
		 * @brief Get the Texture Type
		 *
		 * @return lbTextureType
		 */
		virtual lbTextureType GetTextureType() const = 0;
	};

	class lbTexture2D : public lbTexture
	{
	public:
		using Ptr = std::shared_ptr<lbTexture2D>;
		static Ptr Create(const lbSource::Ptr &source, const lbTextureSpecification &spec = {});
	};

	class lbTextureCube : public lbTexture
	{
	public:
		using Ptr = std::shared_ptr<lbTextureCube>;
		static Ptr Create(const std::array<lbSource::Ptr, 6> &sources, const lbTextureSpecification &spec = {});
	};
}
