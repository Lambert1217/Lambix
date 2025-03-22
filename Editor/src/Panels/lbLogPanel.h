/**
 * @file lbLogPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 日志面板
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbLogPanel : public lbPanel
    {
    public:
        lbLogPanel() = delete;
        lbLogPanel(const std::shared_ptr<lbImGuiSink> &sink);
        ~lbLogPanel() = default;

        using Ptr = std::shared_ptr<lbLogPanel>;
        static Ptr Create(const std::shared_ptr<lbImGuiSink> &sink)
        {
            return std::make_shared<lbLogPanel>(sink);
        }

        // 样式配置
        struct Style
        {
            ImVec4 trace_color = ToImVec4(0xf3ededff);    // (Hex #f3eded)
            ImVec4 info_color = ToImVec4(0x38e93aff);     // (Hex #38e93a)
            ImVec4 warn_color = ToImVec4(0xcee54cff);     // (Hex #cee54c)
            ImVec4 error_color = ToImVec4(0xf34a4aff);    // (Hex #f34a4a)
            ImVec4 critical_color = ToImVec4(0xd79fffff); // (Hex #d79fff)
            int max_lines = 1000;
            bool auto_scroll = true;
        };

        void SetStyle(const Style &new_style) { mStyle = new_style; }

        void OnImGuiRender() override;

    private:
        std::shared_ptr<lbImGuiSink> mSink;
        Style mStyle;
    };
} // namespace Lambix
