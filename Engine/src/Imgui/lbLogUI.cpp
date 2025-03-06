#include "Imgui/lbLogUI.h"

#include <ctime>
#include <iomanip>

namespace Lambix
{

    std::shared_ptr<lbImGuiSink> lbLogUI::s_Sink;
    lbLogUI::Style lbLogUI::s_Style;

    void lbImGuiSink::sink_it_(const spdlog::details::log_msg &msg)
    {
        spdlog::memory_buf_t formatted;
        formatter_->format(msg, formatted);

        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Logs.emplace_back(lbLogEntry{
            msg.level,
            std::string(formatted.data(), formatted.size()),
            std::chrono::system_clock::to_time_t(msg.time)});

        // 保持日志数量在合理范围
        if (m_Logs.size() > m_MaxSize)
        {
            m_Logs.erase(m_Logs.begin(), m_Logs.begin() + (m_Logs.size() - m_MaxSize));
        }
    }

    std::vector<lbLogEntry> lbImGuiSink::GetLogs(bool clear)
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        auto logs = m_Logs;
        if (clear)
            m_Logs.clear();
        return logs;
    }

    void lbImGuiSink::Clear()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Logs.clear();
    }

    void lbLogUI::Init(std::shared_ptr<lbImGuiSink> sink)
    {
        s_Sink = sink;
    }

    void lbLogUI::Draw(bool *p_open)
    {
        if (!s_Sink)
            return;

        if (!ImGui::Begin("Log Viewer", p_open))
        {
            ImGui::End();
            return;
        }

        // 控制栏
        if (ImGui::Button("Clear"))
            s_Sink->Clear();
        ImGui::SameLine();
        ImGui::Checkbox("Auto Scroll", &s_Style.auto_scroll);

        // 日志列表
        ImGui::Separator();
        ImGui::BeginChild("log_list");

        auto logs = s_Sink->GetLogs(false);
        for (const auto &log : logs)
        {
            // 设置颜色
            const ImVec4 *color = &s_Style.info_color;
            switch (log.level)
            {
            case spdlog::level::trace:
                color = &s_Style.trace_color;
                break;
            case spdlog::level::info:
                color = &s_Style.info_color;
                break;
            case spdlog::level::warn:
                color = &s_Style.warn_color;
                break;
            case spdlog::level::err:
                color = &s_Style.error_color;
                break;
            case spdlog::level::critical:
                color = &s_Style.critical_color;
                break;
            }

            // 显示时间戳
            std::tm tm = *std::localtime(&log.timestamp);
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "[%02d:%02d:%02d]",
                               tm.tm_hour, tm.tm_min, tm.tm_sec);
            ImGui::SameLine();

            // 显示日志内容
            ImGui::PushStyleColor(ImGuiCol_Text, *color);
            ImGui::TextWrapped("%s", log.message.c_str());
            ImGui::PopStyleColor();
        }

        // 自动滚动
        if (s_Style.auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }

    void lbLogUI::SetStyle(const Style &new_style)
    {
        s_Style = new_style;
    }

} // namespace Lambix