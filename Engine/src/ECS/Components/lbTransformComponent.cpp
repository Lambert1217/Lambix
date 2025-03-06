#include "lbTransformComponent.h"
#include "ECS/lbEntity.h"
#include "Log/lbLog.h"
#include <glm/gtx/euler_angles.hpp>

namespace Lambix
{
    // 位置设置
    void lbTransformComponent::SetLocalPosition(const glm::vec3 &position)
    {
        if (m_LocalPosition != position)
        {
            m_LocalPosition = position;
            SetDirty(true, false);
        }
    }

    // 旋转设置
    void lbTransformComponent::SetLocalRotation(const glm::quat &rotation)
    {
        if (m_LocalRotation != rotation)
        {
            m_LocalRotation = rotation;
            SetDirty(true, false);
        }
    }

    // 缩放设置
    void lbTransformComponent::SetLocalScale(const glm::vec3 &scale)
    {
        if (m_LocalScale != scale)
        {
            m_LocalScale = scale;
            SetDirty(true, false);
        }
    }

    // 变换操作
    void lbTransformComponent::Translate(const glm::vec3 &translation)
    {
        SetLocalPosition(m_LocalPosition + translation);
    }

    void lbTransformComponent::Rotate(const glm::quat &rotation)
    {
        SetLocalRotation(rotation * m_LocalRotation);
    }

    void lbTransformComponent::Scale(const glm::vec3 &scale)
    {
        SetLocalScale(m_LocalScale * scale);
    }

    void lbTransformComponent::RotateX(float angle)
    {
        Rotate(glm::angleAxis(angle, glm::vec3(1.0f, 0.0f, 0.0f)));
    }

    void lbTransformComponent::RotateY(float angle)
    {
        Rotate(glm::angleAxis(angle, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    void lbTransformComponent::RotateZ(float angle)
    {
        Rotate(glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)));
    }

    void lbTransformComponent::RotateAroundAxis(const glm::vec3 &axis, float angle)
    {
        Rotate(glm::angleAxis(angle, axis));
    }

    const glm::mat4 &lbTransformComponent::GetWorldMatrix()
    {
        if (m_WorldMatrixDirty)
        {
            UpdateWorldMatrix();
        }
        return m_WorldMatrix;
    }

    const glm::mat4 &lbTransformComponent::GetLocalMatrix()
    {
        if (m_LocalMatrixDirty)
        {
            UpdateLocalMatrix();
        }
        return m_LocalMatrix;
    }

    void lbTransformComponent::UpdateWorldMatrix()
    {
        if (m_Parent)
        {
            m_WorldMatrix = m_Parent->GetWorldMatrix() * GetLocalMatrix();
        }
        else
        {
            m_WorldMatrix = GetLocalMatrix();
        }
        m_WorldMatrixDirty = false; // 在此处清除脏位
    }

    void lbTransformComponent::UpdateLocalMatrix()
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_LocalPosition);
        glm::mat4 rotation = glm::mat4_cast(m_LocalRotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_LocalScale);
        m_LocalMatrix = translation * rotation * scale;
        m_LocalMatrixDirty = false; // 在此处清除脏位
    }

    // 世界位置计算（保持原矩阵提取方式）
    glm::vec3 lbTransformComponent::GetWorldPosition()
    {
        return glm::vec3(GetWorldMatrix()[3]);
    }

    glm::vec3 Lambix::lbTransformComponent::GetForward() const
    {
        // 使用旋转四元数计算前向方向（局部坐标系的 Z 轴负方向）
        return m_LocalRotation * glm::vec3(0.0f, 0.0f, -1.0f);
    }

    // 脏位管理
    void lbTransformComponent::SetDirty(bool localDirty, bool worldDirty)
    {
        bool needsPropagation = false;

        // 更新本地脏标记
        if (localDirty && !m_LocalMatrixDirty)
        {
            m_LocalMatrixDirty = true;
            m_WorldMatrixDirty = true; // 本地矩阵脏位更新时，世界矩阵也需要更新
            needsPropagation = true;
        }

        // 更新世界脏标记
        if (worldDirty && !m_WorldMatrixDirty)
        {
            m_WorldMatrixDirty = true;
            needsPropagation = true;
        }

        // 传播到子对象
        if (needsPropagation)
        {
            auto children = GetChildrenTransform();
            for (auto child : children)
            {
                if (child)
                {
                    child->SetDirty(false, true); // 仅传播世界脏标记
                }
            }
        }
    }

    // 层级关系
    std::vector<lbTransformComponent *> lbTransformComponent::GetChildrenTransform()
    {
        std::vector<lbTransformComponent *> children;

        // 1. 获取关联实体
        if (auto entity = m_Entity.lock())
        {
            // 2. 获取场景引用
            auto *scene = entity->GetScene();

            // 3. 获取ChildrenComponent
            if (auto *childrenComp = scene->GetRegistry().try_get<lbChildrenComponent>(*entity))
            {
                // 4. 遍历所有子实体句柄
                for (auto childHandle : childrenComp->m_Children)
                {
                    // 5. 查找有效子实体
                    if (auto it = scene->GetEntityMap().find(childHandle);
                        it != scene->GetEntityMap().end())
                    {
                        // 6. 获取子实体的变换组件
                        if (auto childEntity = it->second)
                        {
                            if (childEntity->HasComponent<lbTransformComponent>())
                            {
                                children.push_back(&childEntity->GetComponent<lbTransformComponent>());
                            }
                        }
                    }
                }
            }
        }

        return children;
    }

    void lbTransformComponent::SetParentTransform(lbTransformComponent *parent)
    {
        m_Parent = parent;
        SetDirty(false, true); // 设置父对象后，需要更新世界矩阵
    }
}
