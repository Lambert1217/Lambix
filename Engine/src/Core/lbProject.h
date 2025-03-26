/**
 * @file lbProject.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 项目
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Assets/lbAssetManager.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    struct lbProjectSpecification
    {
        std::string mName{"untitled"};
        std::filesystem::path mPath;
        std::filesystem::path mAssetPath{"Assets"};
    };

    class lbProject
    {
    public:
        lbProject() = default;
        lbProject(const lbProjectSpecification &spec);
        ~lbProject() = default;

        using Ptr = std::shared_ptr<lbProject>;
        static Ptr Create(const lbProjectSpecification &spec)
        {
            return std::make_shared<lbProject>(spec);
        }
        static Ptr Create()
        {
            return std::make_shared<lbProject>();
        }

        void Init(const lbProjectSpecification &spec);

        bool Serialize();

        bool Deserialize(const std::filesystem::path &path);

        lbScene::Ptr GetActiveScene() const { return mActiveScene; }

        lbAssetManager::Ptr GetAssetManager() const { return mAssetManager; }

    private:
        lbProjectSpecification mSpec;      // 项目描述
        lbAssetManager::Ptr mAssetManager; // 项目资产管理器
        lbScene::Ptr mActiveScene;         // 项目当前激活的场景
    };
} // namespace Lambix
