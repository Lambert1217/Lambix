#include "lbTimer.h"
#include "Log/lbLog.h"

namespace Lambix
{
    lbTimer::lbTimer(const std::string &name) : mName(name), mStopped(false)
    {
        mStartTimePoint = std::chrono::high_resolution_clock::now();
    }

    lbTimer::~lbTimer()
    {
        if (!mStopped)
        {
            Stop();
        }
    }

    void lbTimer::Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f;
        mStopped = true;

        lbProfileResults::Get()->mProfileResults[mName] = duration;
    }
} // namespace Lambix
