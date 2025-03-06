/**
 * @file lbBox.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 包围盒
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "glm/glm.hpp"

namespace Lambix
{
    class lbVertexBuffer;
    class lbBox
    {
    public:
        lbBox() = default;
        ~lbBox() = default;

        using Ptr = std::shared_ptr<lbBox>;

        static Ptr Create();

        bool isEmpty();

        void setFromBuffer(const std::shared_ptr<lbVertexBuffer> &buffer);

        glm::vec3 GetCenter();

    public:
        glm::vec3 m_Min = glm::vec3(std::numeric_limits<float>::infinity());
        glm::vec3 m_Max = glm::vec3(-std::numeric_limits<float>::infinity());
    };
}