/**
 * @file lbSource.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 管理一张图片读入之后的数据，引擎全部采用RGBA
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    struct lbSource
    {
        // 宽高
        uint32_t mWidth{0};
        uint32_t mHeight{0};

        // 读入的数据
        std::vector<std::byte> mData{};

        // 是否需要更新
        bool mNeedsUpdate{true};

        // 有可能有多个texture引用了同一个source，所以source必须有一个缓存机制,缓存必须是key-value形式
        // 所以每一个source都要有自己的hashCode
        size_t mHashCode{0};

        // 在缓存情况下，refCount记录了本Source当前被多少个对象引用，当引用为0，卸载析构
        uint32_t mRefCount{0};

        // 智能指针管理
        using Ptr = std::shared_ptr<lbSource>;
        static Ptr Create()
        {
            return std::make_shared<lbSource>();
        }
    };
} // namespace Lambix
