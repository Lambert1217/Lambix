/**
 * @file lbDriverAttribute.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Renderer/lbAttribute.h"
#include "Renderer/Interfaces/lbBuffer.h"

namespace Lambix
{
    class lbDriverAttribute
    {
    public:
        lbDriverAttribute();
        ~lbDriverAttribute();

        using Ptr = std::shared_ptr<lbDriverAttribute>;
        static Ptr Create()
        {
            return std::make_shared<lbDriverAttribute>();
        }

        void SetBuffer(const lbBuffer::Ptr &buffer) { mBuffer = buffer; }
        lbBuffer::Ptr GetBuffer() const { return mBuffer; }

    private:
        // vbo / ebo
        lbBuffer::Ptr mBuffer;
    };

    class lbDriverAttributes
    {
    public:
        lbDriverAttributes();
        ~lbDriverAttributes();

        using lbDriverAttributesMap = std::unordered_map<lbUUID, lbDriverAttribute::Ptr>;
        using Ptr = std::shared_ptr<lbDriverAttributes>;
        static Ptr Create()
        {
            return std::make_shared<lbDriverAttributes>();
        }

        template <typename T>
        lbDriverAttribute::Ptr OnUpdate(const std::shared_ptr<lbAttribute<T>> &attribute, const lbBufferType &bufferType);

        template <typename T>
        lbDriverAttribute::Ptr Get(const std::shared_ptr<lbAttribute<T>> &attribute);

        void remove(lbUUID attributeID);

        void OnAttributeDispose(const lbEvent::Ptr &event);

    private:
        lbDriverAttributesMap mAttributes{};
    };

    template <typename T>
    inline lbDriverAttribute::Ptr lbDriverAttributes::OnUpdate(const std::shared_ptr<lbAttribute<T>> &attribute, const lbBufferType &bufferType)
    {
        lbDriverAttribute::Ptr dAttribute = nullptr;

        // 先根据ID寻找其对应的lbDriverAttribute
        auto iter = mAttributes.find(attribute->GetID());
        if (iter != mAttributes.end())
        {
            // 找到直接赋值
            dAttribute = iter->second;
        }
        else
        {
            // 没找到，创建，也就是创建vbo
            dAttribute = lbDriverAttribute::Create();
            lbBufferSpecification spec;
            {
                spec.bufferAllocType = attribute->GetBufferAllocType();
                spec.bufferType = bufferType;
                spec.dataType = attribute->GetDataType();
            }
            dAttribute->SetBuffer(lbBuffer::Create(spec));
            dAttribute->GetBuffer()->Bind();
            const auto &data = attribute->GetData();
            dAttribute->GetBuffer()->SetData(data.data(), data.size());
            dAttribute->GetBuffer()->Unbind();

            mAttributes.insert(std::make_pair(attribute->GetID(), dAttribute));

            // 将Attribute的需要更新的状态清空
            attribute->clearUpdateRange();
            attribute->clearNeedsUpdate();
        }

        // 如果原来就存在DriverAttribute，那么就得检查是否需要更新
        if (attribute->GetNeedsUpdate())
        {
            attribute->clearNeedsUpdate();

            const lbRange &range = attribute->GetUpdateRange();
            const auto &data = attribute->GetData();

            dAttribute->GetBuffer()->Bind();

            if (range.mCount > 0)
            {
                dAttribute->GetBuffer()->SetSubData(data.data(), range);
            }
            else
            {
                dAttribute->GetBuffer()->SetData(data.data(), data.size());
            }

            dAttribute->GetBuffer()->Unbind();

            attribute->clearUpdateRange();
        }

        return dAttribute;
    }

    template <typename T>
    inline lbDriverAttribute::Ptr lbDriverAttributes::Get(const std::shared_ptr<lbAttribute<T>> &attribute)
    {
        auto iter = mAttributes.find(attribute->GetID());
        if (iter != mAttributes.end())
        {
            return iter->second;
        }

        return nullptr;
    }
} // namespace Lambix
