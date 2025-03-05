/**
 ***************************************************************
 * @file            : lbResourceManager.h
 * @author          : Lambert
 * @brief           : 统一资源管理系统（Shader/Texture/Geometry）
 * @attention       : 实现资源的创建、缓存和生命周期管理
 * @data            : 2024-11-25
 ***************************************************************
 */
#pragma once

#include "Core/Renderer/lbShader.h"
#include "Core/Renderer/lbTexture.h"
#include "Core/Renderer/Geometry/lbGeometry.h"
#include <unordered_map>
#include <mutex>

namespace Lambix
{
    class lbResourceManager
    {
    public:
        // 获取单例实例
        static lbResourceManager &GetInstance();

        void CleanUnusedResources();

        // Shader管理
        std::shared_ptr<lbShaderProgram> GetShaderProgram(
            const std::string &vertexPath,
            const std::string &fragmentPath);

        // Texture管理  仅支持路径创建
        // 通过路径获取/创建纹理（自动缓存）
        std::shared_ptr<lbTexture> GetTexture(const std::string &path);

        // 纯白1*1
        std::shared_ptr<lbTexture> PureWhite1_1;

    private:
        lbResourceManager() { Init(); }
        ~lbResourceManager() = default;

        void Init();

        // Shader缓存
        struct ShaderProgramKey
        {
            std::string vertexPath;
            std::string fragmentPath;

            bool operator==(const ShaderProgramKey &other) const
            {
                return vertexPath == other.vertexPath &&
                       fragmentPath == other.fragmentPath;
            }
        };

        struct KeyHash
        {
            size_t operator()(const ShaderProgramKey &k) const
            {
                return std::hash<std::string>()(k.vertexPath) ^
                       (std::hash<std::string>()(k.fragmentPath) << 1);
            }
        };

        std::unordered_map<ShaderProgramKey,
                           std::weak_ptr<lbShaderProgram>, KeyHash>
            m_shaderProgramCache;

        // Texture
        // 路径缓存表（key=文件路径）
        std::unordered_map<std::string, std::weak_ptr<lbTexture>> m_texturePathCache;

        // 线程安全
        std::mutex m_shaderMutex;
        std::mutex m_textureMutex;
    };
}
