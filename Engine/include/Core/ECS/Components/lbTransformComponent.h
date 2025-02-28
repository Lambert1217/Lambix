/**
 * @file lbTransformComponent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 变换组件
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Lambix
{
    class lbEntity;
    class lbTransformComponent
    {
    public:
        // 构造函数
        lbTransformComponent() = default;

        // 本地变换属性
        const glm::vec3 &GetLocalPosition() const { return m_LocalPosition; }
        const glm::quat &GetLocalRotation() const { return m_LocalRotation; }
        const glm::vec3 &GetLocalScale() const { return m_LocalScale; }

        // 世界空间属性
        glm::vec3 GetWorldPosition();

        // 矩阵访问
        const glm::mat4 &GetWorldMatrix();
        const glm::mat4 &GetLocalMatrix();

        // 变换设置函数
        void SetLocalPosition(const glm::vec3 &position);
        void SetLocalRotation(const glm::quat &rotation);
        void SetLocalScale(const glm::vec3 &scale);

        // 变换操作
        void Translate(const glm::vec3 &translation);
        void Rotate(const glm::quat &rotation);
        void Scale(const glm::vec3 &scale);

        void RotateX(float angle);
        void RotateY(float angle);
        void RotateZ(float angle);

        void RotateAroundAxis(const glm::vec3 &axis, float angle);

        // 脏位管理
        bool IsDirty() const { return m_Dirty || (m_Parent && m_Parent->IsDirty()); }
        void SetDirty(bool dirty = true);

        // 层级关系
        std::vector<lbTransformComponent *> GetChildrenTransform();
        void SetParentTransform(lbTransformComponent *parent);
        void LinkToEntity(const std::shared_ptr<lbEntity> &entity) { m_Entity = entity; }

    private:
        // 本地变换
        glm::vec3 m_LocalPosition{0.0f};
        glm::quat m_LocalRotation{1.0f, 0.0f, 0.0f, 0.0f}; // 单位四元数
        glm::vec3 m_LocalScale{1.0f};

        // 矩阵缓存
        glm::mat4 m_LocalMatrix{1.0f};
        glm::mat4 m_WorldMatrix{1.0f};

        // 层级关系
        lbTransformComponent *m_Parent = nullptr;
        std::weak_ptr<lbEntity> m_Entity;
        bool m_Dirty = true;

        // 矩阵更新
        void UpdateWorldMatrix();
        void UpdateLocalMatrix();
    };
}
