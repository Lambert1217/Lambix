#include "lbDriverInfo.h"

namespace Lambix
{
    void lbDriverInfo::reset()
    {
        mRender.mFrame++;
        mRender.mCalls = 0;
        mRender.mTriangels = 0;
    }
} // namespace Lambix
