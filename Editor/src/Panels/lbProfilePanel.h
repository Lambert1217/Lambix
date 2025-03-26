/**
 * @file lbProfilePanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 性能分析面板
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"
#include "Utils/lbTimer.h"

namespace Lambix
{
    class lbProfilePanel : public lbPanel
    {
    public:
        lbProfilePanel() = default;
        lbProfilePanel(lbRendererSystem *rendererSystem) : mRendererSystem(rendererSystem) {}
        ~lbProfilePanel() override = default;

        using Ptr = std::shared_ptr<lbProfilePanel>;
        static Ptr Create(lbRendererSystem *rendererSystem)
        {
            return std::make_shared<lbProfilePanel>(rendererSystem);
        }
        static Ptr Create()
        {
            return std::make_shared<lbProfilePanel>();
        }

        void SetContext(lbRendererSystem *rendererSystem) { mRendererSystem = rendererSystem; }

        void OnImGuiRender() override;

    private:
        lbRendererSystem *mRendererSystem{nullptr};
    };
} // namespace Lambix
