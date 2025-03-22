/**
 * @file lbMenuBarPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 菜单栏
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbMenuBarPanel : public lbPanel
    {
    public:
        lbMenuBarPanel() = default;
        ~lbMenuBarPanel() = default;

        using Ptr = std::shared_ptr<lbMenuBarPanel>;
        static Ptr Create()
        {
            return std::make_shared<lbMenuBarPanel>();
        }

        void OnImGuiRender() override;
    };
} // namespace Lambix
