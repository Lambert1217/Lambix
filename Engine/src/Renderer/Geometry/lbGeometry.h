/**
 * @file lbGeometry.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 管理几何数据（顶点属性、索引），并关联到顶点数组对象（VAO）
 * @date 2025-03-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Renderer/lbVertexArray.h"
#include "Renderer/lbBuffer.h"
#include "Math/lbBox.h"
#include "Math/lbSphere.h"

namespace Lambix
{
    class lbGeometry : public std::enable_shared_from_this<lbGeometry>
    {
    public:
        using Ptr = std::shared_ptr<lbGeometry>;
        static Ptr Create() { return std::make_shared<lbGeometry>(); }

        lbGeometry();
        ~lbGeometry();

        // 添加/获取顶点属性（如位置、法线）
        void SetAttribute(const std::string &name, const std::shared_ptr<lbVertexBuffer> &buffer);
        std::shared_ptr<lbVertexBuffer> GetAttribute(const std::string &name) const;

        // 设置索引缓冲区
        void SetIndexBuffer(const std::shared_ptr<lbIndexBuffer> &indexBuffer);

        // 获取关联的 VAO
        std::shared_ptr<lbVertexArray> GetVertexArray() const { return m_vertexArray; }

        // 包围盒计算
        void ComputeBoundingBox();
        lbBox::Ptr GetBoundingBox() const { return m_boundingBox; }

        // 包围球计算
        void ComputeBoundingSphere();
        lbSphere::Ptr GetBoundingSphere() const { return m_boundingSphere; }

    private:
        std::shared_ptr<lbVertexArray> m_vertexArray; // 关联的 VAO
        std::unordered_map<std::string, std::shared_ptr<lbVertexBuffer>> m_attributes;
        lbBox::Ptr m_boundingBox;
        lbSphere::Ptr m_boundingSphere;
    };
}