#include "lbDriverGeometry.h"

namespace Lambix
{
    lbDriverGeometries::lbDriverGeometries(const lbDriverAttributes::Ptr &attributes, const lbDriverInfo::Ptr &info, const lbDriverBindingStates::Ptr &bindingStates)
    {
        mAttributes = attributes;
        mInfo = info;
        mBindingStates = bindingStates;

        lbEventDispatcher::Get()->addEventListener<lbDriverGeometries>("lbGeometryDispose", this, &lbDriverGeometries::OnGeometryDispose);
    }

    lbDriverGeometries::~lbDriverGeometries()
    {
        lbEventDispatcher::Get()->removeEventListener<lbDriverGeometries>("lbGeometryDispose", this, &lbDriverGeometries::OnGeometryDispose);
    }

    void lbDriverGeometries::OnGeometryDispose(const lbEvent::Ptr &event)
    {
        lbUUID id = *((lbUUID *)event->m_UserData);

        mGeometries.erase(id);

        // 因为一个geometry会对应一个driverBindingState，即一个vao
        mBindingStates->ReleaseStateOfGeometry(id);

        mInfo->mMemory.mGeometries--;
    }

    lbGeometry::Ptr lbDriverGeometries::Get(const lbGeometry::Ptr &geometry)
    {
        auto iter = mGeometries.find(geometry->GetID());
        if (iter != mGeometries.end())
        {
            if (iter->second == true)
            {
                return geometry;
            }
        }

        mGeometries[geometry->GetID()] = true;

        mInfo->mMemory.mGeometries++;

        return geometry;
    }

    void lbDriverGeometries::OnUpdate(const lbGeometry::Ptr &geometry)
    {
        const auto frame = mInfo->mRender.mFrame;
        if (frame == geometry->GetLastFrame())
        {
            return;
        }
        const auto &geometryAttributes = geometry->GetAttributes();
        for (const auto &iter : geometryAttributes)
        {
            // 只处理除indexAttribute之外的attributes
            mAttributes->OnUpdate(iter.second, lbBufferType::ArrayBuffer);
        }
        geometry->SetLastFrame(frame);
    }

} // namespace Lambix
