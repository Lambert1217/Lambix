/**
 * @file lbBox.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 包围盒
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "glm/glm.hpp"
#include "Renderer/lbAttribute.h"

namespace Lambix
{
    class lbBox
    {
    public:
        lbBox() = default;
        ~lbBox() = default;

        using Ptr = std::shared_ptr<lbBox>;

        static Ptr Create();

        bool isEmpty();

        void SetFromAttribute(const lbAttributef::Ptr &attribute);

        glm::vec3 GetCenter();

    public:
        glm::vec3 mMin = glm::vec3(std::numeric_limits<float>::infinity());
        glm::vec3 mMax = glm::vec3(-std::numeric_limits<float>::infinity());
    };
}