/**
 * @file lbSphere.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 包围球
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "glm/glm.hpp"

namespace Lambix
{
    class lbSphere
    {
    public:
        lbSphere() = default;
        lbSphere(const glm::vec3 &center, float radius) : m_Center(center), m_Radius(radius) {}
        ~lbSphere() = default;

        using Ptr = std::shared_ptr<lbSphere>;

        static Ptr Create(const glm::vec3 &center, float radius);

        void copy(const lbSphere::Ptr &other);

        void ApplyMatrix4(const glm::mat4 &matrix);

    public:
        glm::vec3 m_Center = glm::vec3(0.0f);
        float m_Radius{0.0f};
    };
}