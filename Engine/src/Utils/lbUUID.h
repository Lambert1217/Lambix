/**
 * @file lbUUID.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief UUID生成器
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    using lbUUID = uint64_t;

    static lbUUID GenUUID()
    {
        static lbUUID s_UUID = 0;
        return s_UUID++;
    }
}