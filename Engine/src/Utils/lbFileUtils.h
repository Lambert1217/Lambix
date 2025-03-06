/**
 * @file lbFileUtils.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 一些文件操作相关的功能
 * @date 2025-01-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

namespace Lambix
{
    const std::string lbResRootDir = "../Assets";

    // 写一个方法拼接两个字符串
    std::string lbJoinPath(const std::string &path1, const std::string &path2);
}