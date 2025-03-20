/**
 * @file lbTextureLoader.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 纹理加载器
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Renderer/Interfaces/lbTexture.h"

namespace Lambix
{
    static uint32_t toStbImageFormat(const lbTextureFormat &format);

    class lbTextureLoader
    {
    public:
        // 从文件加载
        static lbTexture2D::Ptr LoadFromFile(const std::filesystem::path &path);

        // 从内存加载
        static lbTexture2D::Ptr LoadFromMemory(const void *data, size_t size);

        // 创建纯色纹理 1*1  RGBA
        static lbTexture2D::Ptr CreateSolidColor(uint32_t color);

        // 立方体贴图加载
        static lbTextureCube::Ptr LoadCubeMap(const std::array<std::filesystem::path, 6> &paths);

    private:
        static lbSource::Ptr LoadImageFile(const std::filesystem::path &path);
        static lbSource::Ptr CreateSourceFromData(const void *data, uint32_t width, uint32_t height, int channels);
        static lbTextureSpecification GenTextureSpecFromSource(lbSource::Ptr source);
    };
} // namespace Lambix
