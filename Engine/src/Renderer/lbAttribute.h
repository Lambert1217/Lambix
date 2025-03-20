/**
 * @file lbAttribute.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 记录顶点的属性，比如 position color
 * @date 2025-03-10
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Core/lbCore.h"
#include "Events/lbEventPool.h"
#include "Log/lbLog.h"

namespace Lambix
{
    template <typename T>
    class lbAttribute : public std::enable_shared_from_this<lbAttribute<T>>
    {
    public:
        lbAttribute(const std::vector<T> &data, uint32_t itemSize, lbBufferAllocType bufferAllocType = lbBufferAllocType::StaticDrawBuffer);
        ~lbAttribute();

        using Ptr = std::shared_ptr<lbAttribute<T>>;
        static Ptr Create(const std::vector<T> &data, uint32_t itemSize, lbBufferAllocType bufferAllocType = lbBufferAllocType::StaticDrawBuffer)
        {
            return std::make_shared<lbAttribute<T>>(data, itemSize, bufferAllocType);
        }

        // 将value设置到第index个顶点的x值上
        void SetX(const uint32_t &index, T value) noexcept;

        void SetY(const uint32_t &index, T value) noexcept;

        void SetZ(const uint32_t &index, T value) noexcept;

        // 得到第index个顶点的本attribute的x值
        T GetX(const uint32_t &index) noexcept;

        T GetY(const uint32_t &index) noexcept;

        T GetZ(const uint32_t &index) noexcept;

        const auto &GetID() const noexcept { return mID; }

        const auto &GetData() const noexcept { return mData; }

        auto GetCount() const noexcept { return mCount; }

        auto GetItemSize() const noexcept { return mItemSize; }

        bool GetNeedsUpdate() const noexcept { return mNeedsUpdate; }

        void clearNeedsUpdate() noexcept { mNeedsUpdate = false; }

        auto GetBufferAllocType() const noexcept { return mBufferAllocType; }

        const lbRange &GetUpdateRange() const noexcept { return mUpdateRange; }

        void clearUpdateRange() { mUpdateRange = {}; }

        auto GetDataType() const { return mDataType; }

    private:
        lbUUID mID{0};          // 全局唯一ID
        std::vector<T> mData{}; // 数据
        uint32_t mItemSize{0};  // 几个数据为一个顶点的数据
        uint32_t mCount{0};     // 顶点个数

        lbBufferAllocType mBufferAllocType{lbBufferAllocType::StaticDrawBuffer}; // buffer分配类型，分静态和动态

        lbDataType mDataType{lbDataType::FloatType}; // 数据的类型

        bool mNeedsUpdate{true}; // 是否需要更新
        lbRange mUpdateRange{};  // 允许局部更新
    };

    using lbAttributef = lbAttribute<float>;
    using lbAttributei = lbAttribute<uint32_t>;

    template <typename T>
    inline lbAttribute<T>::lbAttribute(const std::vector<T> &data, uint32_t itemSize, lbBufferAllocType bufferAllocType)
        : mData(data), mItemSize(itemSize), mBufferAllocType(bufferAllocType)
    {
        mID = GenUUID();
        mCount = static_cast<uint32_t>(mData.size()) / itemSize;
        mDataType = tolbDataType<T>();
    }

    template <typename T>
    inline lbAttribute<T>::~lbAttribute()
    {
        // 发出销毁事件
        lbEvent::Ptr event = lbEventPool::Get()->Acquire();
        event->Set("lbAttributeDispose", this, &mID);
        lbEventDispatcher::Get()->dispatchEvent(event);
    }

    template <typename T>
    inline void lbAttribute<T>::SetX(const uint32_t &index, T value) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds.");
        LOG_ASSERT(mItemSize >= 1, "mItemSize must be not less than 1.");

        mData[index * mItemSize] = value;
        mNeedsUpdate = true;
    }

    template <typename T>
    inline void lbAttribute<T>::SetY(const uint32_t &index, T value) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds");
        LOG_ASSERT(mItemSize >= 2, "mItemSize must be not less than 2.");

        mData[index * mItemSize + 1] = value;
        mNeedsUpdate = true;
    }

    template <typename T>
    inline void lbAttribute<T>::SetZ(const uint32_t &index, T value) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds");
        LOG_ASSERT(mItemSize >= 3, "mItemSize must be not less than 3.");

        mData[index * mItemSize + 2] = value;
        mNeedsUpdate = true;
    }

    template <typename T>
    inline T lbAttribute<T>::GetX(const uint32_t &index) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds.");
        LOG_ASSERT(mItemSize >= 1, "mItemSize must be not less than 1.");

        return mData[index * mItemSize];
    }

    template <typename T>
    inline T lbAttribute<T>::GetY(const uint32_t &index) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds.");
        LOG_ASSERT(mItemSize >= 2, "mItemSize must be not less than 2.");

        return mData[index * mItemSize + 1];
    }

    template <typename T>
    inline T lbAttribute<T>::GetZ(const uint32_t &index) noexcept
    {
        LOG_ASSERT(index < mCount, "Index out of bounds.");
        LOG_ASSERT(mItemSize >= 3, "mItemSize must be not less than 3.");

        return mData[index * mItemSize + 2];
    }
} // namespace Lambix
