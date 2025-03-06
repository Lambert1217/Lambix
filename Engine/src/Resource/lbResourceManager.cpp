/**
 ***************************************************************
 * @file            : lbResourceManager.cpp
 * @author          : Lambert
 * @brief           : 资源管理实现
 * @attention       : 包含资源加载、缓存和复用策略
 * @data            : 2024-11-25
 ***************************************************************
 */
#include "Resource/lbResourceManager.h"
#include "Log/lbLog.h"

namespace Lambix
{
    lbResourceManager &lbResourceManager::GetInstance()
    {
        static lbResourceManager instance;
        return instance;
    }

    void lbResourceManager::Init()
    {
        // 纯白纹理 1*1
        {
            PureWhite1_1 = lbTexture::Create(1, 1);
            uint32_t Data = 0xffffffff;
            PureWhite1_1->SetData(&Data, 1, 1, 0, 0);
        }
    }

    void lbResourceManager::CleanUnusedResources()
    {
        // 清理Shader程序缓存
        {
            std::lock_guard<std::mutex> lock(m_shaderMutex);
            for (auto it = m_shaderProgramCache.begin(); it != m_shaderProgramCache.end();)
            {
                // weak_ptr的expired()方法判断对象是否已被释放
                it->second.expired() ? it = m_shaderProgramCache.erase(it) : ++it;
            }
        }

        // 清理路径纹理缓存
        {
            std::lock_guard<std::mutex> lock(m_textureMutex);
            for (auto it = m_texturePathCache.begin(); it != m_texturePathCache.end();)
            {
                it->second.expired() ? it = m_texturePathCache.erase(it) : ++it;
            }
        }
    }

    // Shader管理实现
    std::shared_ptr<lbShaderProgram> lbResourceManager::GetShaderProgram(
        const std::string &vertexPath,
        const std::string &fragmentPath)
    {
        ShaderProgramKey key{vertexPath, fragmentPath};

        std::lock_guard<std::mutex> lock(m_shaderMutex);

        // 尝试从缓存获取
        if (auto it = m_shaderProgramCache.find(key);
            it != m_shaderProgramCache.end())
        {
            if (auto sp = it->second.lock())
                return sp;
        }

        // 创建新Shader程序
        auto vertexShader = lbShader::Create(lbShaderType::Vertex);
        vertexShader->CompileFromFile(vertexPath);

        auto fragmentShader = lbShader::Create(lbShaderType::Fragment);
        fragmentShader->CompileFromFile(fragmentPath);

        auto program = lbShaderProgram::Create();
        if (!program->Link(vertexShader, fragmentShader))
        {
            LOG_ERROR("Failed to link shader program: {} + {}",
                      vertexPath, fragmentPath);
            return nullptr;
        }

        // 存入缓存
        m_shaderProgramCache[key] = program;
        return program;
    }

    // Texture管理实现
    // 通过文件路径获取纹理（自动缓存）
    std::shared_ptr<lbTexture> lbResourceManager::GetTexture(const std::string &path)
    {
        std::lock_guard<std::mutex> lock(m_textureMutex);

        // 1. 检查路径缓存
        if (auto it = m_texturePathCache.find(path); it != m_texturePathCache.end())
        {
            if (auto tex = it->second.lock())
                return tex;
        }

        // 2. 创建新纹理
        auto texture = lbTexture::Create(path);
        if (!texture)
            return nullptr;

        // 3. 更新缓存
        m_texturePathCache[path] = texture;
        return texture;
    }
}
