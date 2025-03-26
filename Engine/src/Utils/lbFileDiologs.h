/**
 * @file lbFileDiologs.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 文件对话框
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    // FileDiologs
    class lbFileDiologs
    {
    public:
        // 返回空字符串如果取消
        static std::string OpenFile(const char *filter);
        static std::string SaveFile(const char *filter);
    };
} // namespace Lambix
