/**
 * @file lbModel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 模型
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbMesh.h"
#include "glm/glm.hpp"

namespace Lambix
{
    struct lbModelNode
    {
        using Ptr = std::shared_ptr<lbModelNode>;
        static Ptr Create()
        {
            return std::make_shared<lbModelNode>();
        }

        std::string name;                       // 添加名称标识
        glm::mat4 mTransformMatrix;             // 变换
        std::vector<uint32_t> meshIndices;      // 一个节点可关联多个网格
        std::vector<lbModelNode::Ptr> children; // 直接存储子节点指针
    };

    class lbModel
    {
    public:
        lbModel() = default;
        ~lbModel() = default;

        using Ptr = std::shared_ptr<lbModel>;
        static Ptr Create()
        {
            return std::make_shared<lbModel>();
        }

        const lbModelNode::Ptr &GetRoot() const { return m_RootNode; }
        const std::vector<lbMesh::Ptr> &GetMeshes() const { return m_Meshes; }

        // TODO：实现模型多余节点的去除

    private:
        friend class lbModelLoader;
        lbModelNode::Ptr m_RootNode{nullptr}; // 明确根节点
        std::vector<lbMesh::Ptr> m_Meshes;    // 所有网格集中管理
    };
} // namespace Lambix
