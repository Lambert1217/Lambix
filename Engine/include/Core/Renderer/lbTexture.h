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

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		static std::shared_ptr<lbTexture> Create(const std::string& path);
		static std::shared_ptr<lbTexture> Create(uint32_t width, uint32_t height);
	};
}
