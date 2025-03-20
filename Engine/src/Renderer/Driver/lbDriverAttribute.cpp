#include "lbDriverAttribute.h"

namespace Lambix
{
    lbDriverAttribute::lbDriverAttribute()
        : mBuffer(nullptr)
    {
    }

    lbDriverAttribute::~lbDriverAttribute()
    {
    }

    lbDriverAttributes::lbDriverAttributes()
    {
        lbEventDispatcher::Get()->addEventListener<lbDriverAttributes>("lbAttributeDispose", this, &lbDriverAttributes::OnAttributeDispose);
    }

    lbDriverAttributes::~lbDriverAttributes()
    {
        lbEventDispatcher::Get()->removeEventListener<lbDriverAttributes>("lbAttributeDispose", this, &lbDriverAttributes::OnAttributeDispose);
    }

    void lbDriverAttributes::remove(lbUUID attributeID)
    {
        auto iter = mAttributes.find(attributeID);
        if (iter != mAttributes.end())
        {
            mAttributes.erase(iter);
        }
    }

    void lbDriverAttributes::OnAttributeDispose(const lbEvent::Ptr &event)
    {
        lbUUID id = *((lbUUID *)(event->m_UserData));
        remove(id);
    }
} // namespace Lambix
