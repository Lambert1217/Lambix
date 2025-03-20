#include "Math/lbSphere.h"

namespace Lambix
{
    lbSphere::Ptr lbSphere::Create(const glm::vec3 &center, float radius)
    {
        return std::make_shared<lbSphere>(center, radius);
    }

    void lbSphere::copy(const lbSphere::Ptr &other)
    {
        mCenter = other->mCenter;
        mRadius = other->mRadius;
    }

    void lbSphere::ApplyMatrix4(const glm::mat4 &matrix)
    {
        mCenter = glm::vec3(matrix * glm::vec4(mCenter, 1.0f));

        // 对于半径，只会收到scale缩放影响，我们只需要考虑三个Scale当中最大的哪个
        float scaleX = glm::length(glm::vec3(matrix[0]));
        float scaleY = glm::length(glm::vec3(matrix[1]));
        float scaleZ = glm::length(glm::vec3(matrix[2]));
        float maxScale = std::max(std::max(scaleX, scaleY), scaleZ);

        mRadius *= maxScale;
    }
}