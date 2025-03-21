/**
 * @file lbModelLoader.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 模型加载
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Renderer/lbModel.h"

namespace Lambix
{
    class lbModelLoader
    {
    public:
        static lbModel::Ptr LoadFromFile(const std::filesystem::path &path);

    private:
        static void processMaterial(const aiScene *scene, const std::filesystem::path &rootPath, std::vector<lbMaterial::Ptr> &materials);

        static lbTexture2D::Ptr processTexture2D(const aiTextureType &type, const aiScene *scene, const aiMaterial *material, const std::filesystem::path &rootPath);

        static void processNode(const aiNode *node, const aiScene *scene,
                                const lbModelNode::Ptr &parentNode, std::vector<lbMaterial::Ptr> &materials, std::vector<lbMesh::Ptr> &meshes);

        static lbMesh::Ptr processMesh(const aiMesh *mesh, const aiScene *scene, std::vector<lbMaterial::Ptr> &materials);

        static glm::mat4 ToGLMMat4(const aiMatrix4x4 &value);
    };
} // namespace Lambix
