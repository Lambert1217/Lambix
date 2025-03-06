/**
 * @file lbOpenGLUniformBuffer.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include "Core/Renderer/lbUniformBuffer.h"

namespace Lambix
{
    class lbOpenGLUniformBuffer : public lbUniformBuffer
    {
    public:
        explicit lbOpenGLUniformBuffer(const lbUniformBufferSpec &spec);
        ~lbOpenGLUniformBuffer() override;

        void Bind() const override;
        void Unbind() const override;
        void SetData(const void *data, uint32_t size, uint32_t offset) override;

        const lbUniformBufferSpec &GetSpec() const override { return m_Spec; }

    private:
        uint32_t m_RendererID;
        lbUniformBufferSpec m_Spec;
    };
}