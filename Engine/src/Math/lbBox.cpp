#include "Math/lbBox.h"
#include "Log/lbLog.h"
#include "lbBox.h"

namespace Lambix
{
    lbBox::Ptr lbBox::Create()
    {
        return std::make_shared<lbBox>();
    }

    bool lbBox::isEmpty()
    {
        return (mMax.x < mMin.x || mMax.y < mMin.y || mMax.z < mMin.z);
    }

    void lbBox::SetFromAttribute(const lbAttributef::Ptr &attribute)
    {
        for (uint32_t i = 0; i < attribute->GetCount(); ++i)
        {
            float x = attribute->GetX(i);
            float y = attribute->GetY(i);
            float z = attribute->GetZ(i);

            if (x < mMin.x)
            {
                mMin.x = x;
            }
            if (y < mMin.y)
            {
                mMin.y = y;
            }
            if (z < mMin.z)
            {
                mMin.z = z;
            }

            if (x > mMax.x)
            {
                mMax.x = x;
            }
            if (y > mMax.y)
            {
                mMax.y = y;
            }
            if (z > mMax.z)
            {
                mMax.z = z;
            }
        }
    }

    glm::vec3 lbBox::GetCenter()
    {
        if (isEmpty())
        {
            return glm::vec3(0.0f);
        }
        return (mMin + mMax) / 2.0f;
    }
}