/**
 * @file lbFrameBuffer.h
 * @author Lambert1217 (1904310303@qq.com)
 * @brief
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

namespace Lambix
{
    struct lbFrameBufferSpecification
    {
        uint32_t width, height;
        bool SwapChainTarget = false;
    };

    class lbFrameBuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        virtual const lbFrameBufferSpecification &GetSpecification() const = 0;

        static std::shared_ptr<lbFrameBuffer> Create(const lbFrameBufferSpecification &spec);
    };
}