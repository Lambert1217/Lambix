#include "lbGeometry.h"

namespace Lambix
{
    lbGeometry::lbGeometry() : mID(GenUUID())
    {
    }

    lbGeometry::~lbGeometry()
    {
        lbEvent::Ptr event = lbEventPool::Get()->Acquire();
        event->Set("lbGeometryDispose", this, &mID);
        lbEventDispatcher::Get()->dispatchEvent(event);
    }

    void lbGeometry::SetAttribute(const std::string &name, lbAttributef::Ptr attribute) noexcept
    {
        mAttributes[name] = attribute;
    }

    lbAttributef::Ptr lbGeometry::GetAttribute(const std::string &name) noexcept
    {
        auto iter = mAttributes.find(name);
        if (iter != mAttributes.end())
        {
            return iter->second;
        }

        return nullptr;
    }

    void lbGeometry::deleteAttribute(const std::string &name) noexcept
    {
        auto iter = mAttributes.find(name);
        if (iter != mAttributes.end())
        {
            mAttributes.erase(iter);
        }
    }

    bool lbGeometry::hasAttribute(const std::string &name) noexcept
    {
        auto iter = mAttributes.find(name);
        if (iter == mAttributes.end())
        {
            return false;
        }

        return true;
    }

    void lbGeometry::computeBoundingBox() noexcept
    {
        auto position = GetAttribute("a_Position");

        if (position == nullptr)
        {
            LOG_ERROR("geometry has no position when computeBoundingBox");
            return;
        }

        if (mBoundingBox == nullptr)
        {
            mBoundingBox = lbBox::Create();
        }

        mBoundingBox->SetFromAttribute(position);
    }

    void lbGeometry::computeBoundingSphere() noexcept
    {
        computeBoundingBox();
        if (mBoundingSphere == nullptr)
        {
            mBoundingSphere = lbSphere::Create(glm::vec3(0.0f), 0.0f);
        }

        // 包围球跟包围盒共享了一个center
        mBoundingSphere->mCenter = mBoundingBox->GetCenter();

        // find smallest sphere :inscribed sphere
        auto position = GetAttribute("a_Position");

        // 找到距离当前球心最大距离的点
        float maxRadiusSq = 0;
        uint32_t count = position->GetCount();
        for (uint32_t i = 0; i < count; ++i)
        {
            // 把每个顶点的xyz装成一个point
            glm::vec3 point = glm::vec3(position->GetX(i), position->GetY(i), position->GetZ(i));

            // 计算point到center的距离
            glm::vec3 radiusVector = mBoundingSphere->mCenter - point;

            // 原本应该对比每一个点到center的距离，找到最大。但是计算向量长度，必须经过开方这个运算
            // 为了性能考虑，直接记录其平方，最后得到最大值，再开二次方
            maxRadiusSq = glm::max(glm::dot(radiusVector, radiusVector), maxRadiusSq);
        }

        // 开方求取radius
        mBoundingSphere->mRadius = glm::sqrt(maxRadiusSq);
    }
} // namespace Lambix
