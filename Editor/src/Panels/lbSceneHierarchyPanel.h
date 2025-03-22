/**
 * @file lbSceneHierarchyPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 场景层级结构面板
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbSceneHierarchyPanel : public lbPanel
    {
    public:
        lbSceneHierarchyPanel() = delete;
        lbSceneHierarchyPanel(const std::shared_ptr<lbScene> &scene) : mContext(scene) {}
        ~lbSceneHierarchyPanel() override = default;

        using Ptr = std::shared_ptr<lbSceneHierarchyPanel>;
        static Ptr Create(const std::shared_ptr<lbScene> &scene)
        {
            return std::make_shared<lbSceneHierarchyPanel>(scene);
        }

        void SetContext(const std::shared_ptr<lbScene> &scene) { mContext = scene; }

        void OnImGuiRender() override;

    private:
        void DrawEntityNode(const std::shared_ptr<lbEntity> &entity);

    private:
        std::shared_ptr<lbScene> mContext{nullptr};
        std::shared_ptr<lbEntity> mSeletedEntity{nullptr};
    };
} // namespace Lambix
