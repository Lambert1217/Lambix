/**
 * @file lbCache.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 缓存
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Utils/lbSingleton.h"
#include "Utils/lbSource.h"
#include "Renderer/Interfaces/lbShader.h"
#include "Events/lbEventPool.h"

namespace Lambix
{
    class lbCache : public lbSingleton<lbCache>
    {
    public:
        lbCache();
        ~lbCache() override;

        //-------source----------------------------------------------------

        /**
         * @brief Get the Source object
         *
         * @param path
         * @return lbSource::Ptr
         */
        lbSource::Ptr GetSource(const std::string &path);

        /**
         * @brief 缓存source
         *
         * @param path
         * @param source
         */
        void CacheSource(const std::string &path, lbSource::Ptr source);

        /**
         * @brief SourceRelease 事件响应
         *
         * @param event
         */
        void OnSourceRelease(const lbEvent::Ptr &event);

        //-------shader-----------------------------------------------------

        /**
         * @brief Get the Shader Program object
         *
         * @param vertexPath
         * @param fragmentPath
         * @return lbShaderProgram::Ptr
         */
        lbShaderProgram::Ptr GetShaderProgram(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);

        /**
         * @brief ShaderProgramRelease 事件响应
         *
         * @param event
         */
        void OnShaderProgramRelease(const lbEvent::Ptr &event);

    private:
        // sources
        std::unordered_map<size_t, lbSource::Ptr> mSources;
        std::mutex mSourcesMutex;
        // shader
        std::unordered_map<size_t, lbShaderProgram::Ptr> mShaderPrograms;
        std::mutex mShaderProgramsMutex;
    };
} // namespace Lambix
