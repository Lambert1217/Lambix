/**
 * @file lbTransform.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 变换
 * @date 2025-03-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Lambix
{
    class lbTransform
    {
    public:
        lbTransform() = default;
        lbTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

        void SetPosition(const glm::vec3 &position);

        void SetRotation(const glm::vec3 &rotation);

        void SetScale(const glm::vec3 &scale);

        void SetFromMatrix(const glm::mat4 &matrix);

        const glm::vec3 &GetPosition() const { return m_Position; }

        const glm::vec3 &GetRotation() const { return m_Rotation; }

        const glm::vec3 &GetScale() const { return m_Scale; }

        glm::quat GetQuaternion() const;

        glm::vec3 GetFront() const;

        glm::vec3 GetRight() const;

        glm::vec3 GetUp() const;

        void Reset();

        void UpdateWorldMatrix(const glm::mat4 &parentWorldMatrix = glm::mat4(1.0f));

        void Translate(const glm::vec3 &translation);

        void Rotate(const glm::vec3 &eulerAngles);

        void Scale(const glm::vec3 &scale);

        void Scale(float scale);

        void LookAt(const glm::vec3 &target);

        glm::vec3 GetWorldPosition() const { return glm::vec3(m_WorldMatrix[3]); }

        const glm::mat4 &GetWorldMatrix() const { return m_WorldMatrix; }

        void SetDirty();

        bool IsDirty() const { return m_IsDirty; }

        // 回调绑定接口
        void BindDirtyCallback(std::function<void()> callback) { m_OnDirtyCallback = callback; }

    private:
        friend class lbPropertyPanel;
        glm::vec3 m_Position{0.0f};
        glm::vec3 m_Rotation{0.0f};
        glm::vec3 m_Scale{1.0f};
        glm::mat4 m_WorldMatrix{1.0f};
        bool m_IsDirty{true};

        // 脏位设置回调，用于组件中设置子实体为脏
        std::function<void()> m_OnDirtyCallback;
    };
}