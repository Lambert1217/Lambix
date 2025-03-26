/**
 * @file lbAssetsBrowserPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 资产浏览面板
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbAssetsBrowserPanel : public lbPanel
    {
    public:
        lbAssetsBrowserPanel() = default;
        lbAssetsBrowserPanel(const lbAssetManager::Ptr &manager);

        using Ptr = std::shared_ptr<lbAssetsBrowserPanel>;
        static Ptr Create(const lbAssetManager::Ptr &manager)
        {
            return std::make_shared<lbAssetsBrowserPanel>(manager);
        }
        static Ptr Create()
        {
            return std::make_shared<lbAssetsBrowserPanel>();
        }

        void OnImGuiRender() override;

        void SetContext(const lbAssetManager::Ptr &manager);

        lbAssetManager::Ptr GetAssetManager() const { return mAssetManager; }

    private:
        void CreateAsset(const std::filesystem::path &p);

    private:
        lbAssetManager::Ptr mAssetManager{nullptr};
        std::filesystem::path mCurrentPath;
    };
} // namespace Lambix
