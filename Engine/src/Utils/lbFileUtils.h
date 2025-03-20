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
    const std::filesystem::path lbAssetsDir = "../Assets";

    // 写一个方法拼接两个字符串
    std::filesystem::path lbJoinPath(const std::filesystem::path &path1, const std::filesystem::path &path2);
}

#define ASSETS(X) lbJoinPath(lbAssetsDir, X)