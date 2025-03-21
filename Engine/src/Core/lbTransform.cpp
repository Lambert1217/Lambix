#include "lbTransform.h"

namespace Lambix
{
    lbTransform::lbTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
        : m_Position(position), m_Rotation(rotation), m_Scale(scale)
    {
        SetDirty();
    }
    void lbTransform::SetPosition(const glm::vec3 &position)
    {
        if (m_Position != position)
        {
            m_Position = position;
            SetDirty();
        }
    }
    void lbTransform::SetRotation(const glm::vec3 &rotation)
    {
        if (m_Rotation != rotation)
        {
            m_Rotation = rotation;
            SetDirty();
        }
    }
    void lbTransform::SetScale(const glm::vec3 &scale)
    {
        if (m_Scale != scale)
        {
            m_Scale = scale;
            SetDirty();
        }
    }
    void lbTransform::SetFromMatrix(const glm::mat4 &matrix)
    {
        m_WorldMatrix = matrix;
        // decompose
        {
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::quat rotation;
            glm::decompose(m_WorldMatrix, m_Scale, rotation, m_Position, skew, perspective);
            m_Rotation = glm::degrees(glm::eulerAngles(rotation));
        }
        SetDirty();
    }
    glm::quat lbTransform::GetQuaternion() const
    {
        return glm::qua(glm::radians(m_Rotation));
    }
    glm::vec3 lbTransform::GetFront() const
    {
        // 前方向为局部坐标系-Z方向，应用四元数旋转
        return GetQuaternion() * glm::vec3(0.0f, 0.0f, -1.0f);
    }
    glm::vec3 lbTransform::GetRight() const
    {
        // 右方向为+X方向
        return GetQuaternion() * glm::vec3(1.0f, 0.0f, 0.0f);
    }
    glm::vec3 lbTransform::GetUp() const
    {
        // 上方向为+Y方向
        return GetQuaternion() * glm::vec3(0.0f, 1.0f, 0.0f);
    }
    void lbTransform::Reset()
    {
        m_Position = glm::vec3(0.0f);
        m_Rotation = glm::vec3(0.0f);
        m_Scale = glm::vec3(1.0f);
        SetDirty();
    }
    void lbTransform::UpdateWorldMatrix(const glm::mat4 &parentWorldMatrix)
    {
        if (m_IsDirty)
        {
            // 按TRS顺序组合本地矩阵
            const glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
            const glm::mat4 rotate = glm::mat4_cast(GetQuaternion());
            const glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

            const glm::mat4 localMatrix = translate * rotate * scale;
            m_WorldMatrix = parentWorldMatrix * localMatrix;

            m_IsDirty = false;
        }
    }
    void lbTransform::Rotate(const glm::vec3 &eulerAngles)
    {
        glm::quat currentRotation = glm::quat(glm::radians(m_Rotation));
        glm::quat additionalRotation = glm::quat(glm::radians(eulerAngles));
        m_Rotation = glm::degrees(glm::eulerAngles(currentRotation * additionalRotation));
        SetDirty();
    }
    void lbTransform::LookAt(const glm::vec3 &target)
    {
        glm::vec3 direction = glm::normalize(target - m_Position);

        float pitch = glm::asin(direction.y);
        float yaw = glm::atan(-direction.x, -direction.z);

        m_Rotation.x = glm::degrees(pitch);
        m_Rotation.y = glm::degrees(yaw);
        m_Rotation.z = 0.0f;

        SetDirty();
    }
    void lbTransform::SetDirty()
    {
        m_IsDirty = true;
        if (m_OnDirtyCallback)
            m_OnDirtyCallback();
    }
}