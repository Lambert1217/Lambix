/**
 * @file lbTimer.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 计时器，可用于性能检测
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbSingleton.h"

namespace Lambix
{
    class lbTimer
    {
    public:
        lbTimer(const std::string &name);
        ~lbTimer();

        void Stop();

    private:
        std::string mName;
        std::chrono::time_point<std::chrono::steady_clock> mStartTimePoint;
        bool mStopped;
    };

    class lbProfileResults : public lbSingleton<lbProfileResults>
    {
    public:
        const std::unordered_map<std::string, float> &GetResults() const { return mProfileResults; }

    private:
        friend class lbTimer;
        std::unordered_map<std::string, float> mProfileResults;
    };
} // namespace Lambix

#define PROFILE_SCOPE(name) Lambix::lbTimer timer##__LINE__(name)
