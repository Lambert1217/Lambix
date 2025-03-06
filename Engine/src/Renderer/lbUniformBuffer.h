/**
 * @file lbUniformBuffer.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    struct lbUniformBufferSpec
    {
        uint32_t size;        // Buffer总字节数
        uint32_t binding;     // 绑定点索引
        bool dynamic = false; // 是否支持动态更新
    };

    class lbUniformBuffer
    {
    public:
        virtual ~lbUniformBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetData(const void *data, uint32_t size, uint32_t offset = 0) = 0;

        virtual const lbUniformBufferSpec &GetSpec() const = 0;

        static std::shared_ptr<lbUniformBuffer> Create(const lbUniformBufferSpec &spec);
    };
}