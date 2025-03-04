#include "Core/Math/lbSphere.h"

namespace Lambix
{
    lbSphere::Ptr lbSphere::Create(const glm::vec3 &center, float radius)
    {
        return std::make_shared<lbSphere>(center, radius);
    }

    void lbSphere::copy(const lbSphere::Ptr &other)
    {
        m_Center = other->m_Center;
        m_Radius = other->m_Radius;
    }

    void lbSphere::ApplyMatrix4(const glm::mat4 &matrix)
    {
        m_Center = glm::vec3(matrix * glm::vec4(m_Center, 1.0f));

        // 对于半径，只会收到scale缩放影响，我们只需要考虑三个Scale当中最大的哪个
        float scaleX = glm::length(glm::vec3(matrix[0]));
        float scaleY = glm::length(glm::vec3(matrix[1]));
        float scaleZ = glm::length(glm::vec3(matrix[2]));
        float maxScale = std::max(std::max(scaleX, scaleY), scaleZ);

        m_Radius *= maxScale;
    }
}