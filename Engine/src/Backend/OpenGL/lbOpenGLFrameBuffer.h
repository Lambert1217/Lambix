/**
 * @file lbOpenGLFrameBuffer.h
 * @author Lambert1217 (1904310303@qq.com)
 * @brief
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Renderer/lbFrameBuffer.h"

namespace Lambix
{

    class lbOpenGLFrameBuffer : public lbFrameBuffer
    {
    public:
        lbOpenGLFrameBuffer(const lbFrameBufferSpecification &spec);
        ~lbOpenGLFrameBuffer();

        void Bind() override;
        void Unbind() override;

        void Resize(uint32_t width, uint32_t height) override;

        void Invalidate();

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
        const lbFrameBufferSpecification &GetSpecification() const override { return m_Specification; }

    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        lbFrameBufferSpecification m_Specification;
    };
}