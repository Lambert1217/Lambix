#include "lbCache.h"
#include "Log/lbLog.h"

namespace Lambix
{
    lbCache::lbCache()
    {
        lbEventDispatcher::Get()->addEventListener<lbCache>("SourceRelease", this, &lbCache::OnSourceRelease);
        lbEventDispatcher::Get()->addEventListener<lbCache>("ShaderProgramRelease", this, &lbCache::OnShaderProgramRelease);
    }

    lbCache::~lbCache()
    {
        lbEventDispatcher::Get()->removeEventListener<lbCache>("SourceRelease", this, &lbCache::OnSourceRelease);
        lbEventDispatcher::Get()->removeEventListener<lbCache>("ShaderProgramRelease", this, &lbCache::OnShaderProgramRelease);
    }

    // sources
    lbSource::Ptr lbCache::GetSource(const std::string &path)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        const auto hash = std::hash<std::string>{}(path);

        if (auto it = mSources.find(hash); it != mSources.end())
        {
            it->second->mRefCount++;
            return it->second;
        }
        return nullptr;
    }

    void lbCache::CacheSource(const std::string &path, lbSource::Ptr source)
    {
        std::lock_guard<std::mutex> lock(mSourcesMutex);
        const auto hash = std::hash<std::string>{}(path);

        if (!mSources.contains(hash))
        {
            source->mHashCode = hash;
            source->mRefCount++;
            mSources.emplace(hash, source);
        }
    }

    void lbCache::OnSourceRelease(const lbEvent::Ptr &event)
    {
        auto source = static_cast<lbSource *>(event->m_Emitter);
        auto hashCode = source->mHashCode;

        std::lock_guard<std::mutex> lock(mSourcesMutex);

        auto iter = mSources.find(hashCode);
        if (iter == mSources.end())
        {
            return;
        }

        // 如果确实存在在cache里面，则引用计数-1
        source->mRefCount--;

        // 如果引用计数 = 0，说明整个程序没有人再使用这个source，那么就从cache里清除
        if (source->mRefCount == 0)
        {

            // source通过sharedPtr管理，那么再erase之后，并且以前持有他的对象都不再持有，
            // source这个智能指针的引用计数变为了0，则会构成source的析构
            mSources.erase(iter);
        }
    }

    // shader
    lbShaderProgram::Ptr lbCache::GetShaderProgram(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
    {
        // 生成唯一哈希键
        const std::string combined = vertexPath.string() + "|" + fragmentPath.string();
        const size_t key = std::hash<std::string>{}(combined);

        std::lock_guard<std::mutex> lock(mShaderProgramsMutex);

        // 查找缓存
        if (auto it = mShaderPrograms.find(key); it != mShaderPrograms.end())
        {
            it->second->GetRefCount()++;
            return it->second;
        }

        // 创建新的ShaderProgram
        auto vertexShader = lbShader::Create(lbShaderType::Vertex);
        auto fragmentShader = lbShader::Create(lbShaderType::Fragment);

        vertexShader->CompileFromFile(vertexPath);
        fragmentShader->CompileFromFile(fragmentPath);

        auto program = lbShaderProgram::Create();
        if (!program->Link(vertexShader, fragmentShader))
        {
            LOG_ERROR("Failed to link shader program: {} + {}", vertexPath.string(), fragmentPath.string());
            return nullptr;
        }

        // 加入缓存
        program->GetRefCount()++;
        program->GetHashCode() = key;
        mShaderPrograms.emplace(key, program);
        return program;
    }

    void lbCache::OnShaderProgramRelease(const lbEvent::Ptr &event)
    {
        auto shaderProgram = static_cast<lbShaderProgram *>(event->m_Emitter);
        auto hashCode = shaderProgram->GetHashCode();

        std::lock_guard<std::mutex> lock(mShaderProgramsMutex);

        auto iter = mShaderPrograms.find(hashCode);
        if (iter == mShaderPrograms.end())
        {
            return;
        }

        // 如果确实存在在cache里面，则引用计数-1
        shaderProgram->GetRefCount()--;

        // 如果引用计数 = 0，说明整个程序没有人再使用这个shaderProgram，那么就从cache里清除
        if (shaderProgram->GetRefCount() == 0)
        {
            mShaderPrograms.erase(iter);
        }
    }
} // namespace Lambix
