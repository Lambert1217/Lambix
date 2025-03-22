/**
 * @file lbViewportPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 视口面板
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbViewportPanel : public lbPanel
    {
    public:
        lbViewportPanel() = delete;
        lbViewportPanel(const std::shared_ptr<lbScene> &scene);
        ~lbViewportPanel() = default;

        using Ptr = std::shared_ptr<lbViewportPanel>;
        static Ptr Create(const std::shared_ptr<lbScene> &scene)
        {
            return std::make_shared<lbViewportPanel>(scene);
        }

        void OnImGuiRender() override;

    private:
        std::shared_ptr<lbScene> mScene{nullptr};
    };
} // namespace Lambix
