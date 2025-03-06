/**
 * @file lbLogUI.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief ImGui显示模块头文件
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <imgui.h>
#include <spdlog/common.h>
#include <spdlog/sinks/base_sink.h>

namespace Lambix
{

    struct lbLogEntry
    {
        spdlog::level::level_enum level;
        std::string message;
        std::time_t timestamp;
    };

    class lbImGuiSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        // 获取日志条目（带自动清理）
        std::vector<lbLogEntry> GetLogs(bool clear = true);

        // 清空日志
        void Clear();

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) override;
        void flush_() override {}

    private:
        std::vector<lbLogEntry> m_Logs;
        std::mutex m_Mutex;
        size_t m_MaxSize = 1000;
    };

    class lbLogUI
    {
    public:
        // 初始化显示系统
        static void Init(std::shared_ptr<lbImGuiSink> sink);

        // 绘制日志窗口
        static void Draw(bool *p_open = nullptr);

        // 样式配置
        struct Style
        {
            ImVec4 trace_color = {0.4f, 0.4f, 0.4f, 1.0f};    // 中性灰 (Hex #666666)
            ImVec4 info_color = {0.0f, 0.4f, 0.8f, 1.0f};     // 品牌蓝 (Hex #0066CC)
            ImVec4 warn_color = {0.9f, 0.6f, 0.0f, 1.0f};     // 琥珀橙 (Hex #E69500)
            ImVec4 error_color = {0.8f, 0.1f, 0.1f, 1.0f};    // 警示红 (Hex #CC1A1A)
            ImVec4 critical_color = {0.6f, 0.0f, 0.6f, 1.0f}; // 深紫色 (Hex #990099)
            int max_lines = 1000;
            bool auto_scroll = true;
        };

        static void SetStyle(const Style &new_style);

    private:
        static std::shared_ptr<lbImGuiSink> s_Sink;
        static Style s_Style;
    };

} // namespace Lambix
