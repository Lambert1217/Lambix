#include "lbDriverInfo.h"

namespace Lambix
{
    void lbDriverInfo::reset()
    {
        if (mRender.mDurationTime >= 1)
        {
            mRender.FPS = mRender.mFrame;
            mRender.mFrame = -1;
            mRender.mDurationTime = 0;
        }
        mRender.mFrame++;
        mRender.mCalls = 0;
        mRender.mTriangels = 0;
    }
} // namespace Lambix
