/**
 * @file lbDriverInfo.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 记录一些渲染信息
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    struct lbDriverInfo
    {
        struct Memory
        {
            uint32_t mGeometries{0};
            uint32_t mTextures{0};
        };

        struct Render
        {
            uint32_t mFrame{0};
            uint32_t mCalls{0};
            uint32_t mTriangels{0};
        };

        lbDriverInfo() = default;
        ~lbDriverInfo() = default;

        using Ptr = std::shared_ptr<lbDriverInfo>;
        static Ptr Create()
        {
            return std::make_shared<lbDriverInfo>();
        }

        void reset();

        Memory mMemory{};
        Render mRender{};
    };
} // namespace Lambix