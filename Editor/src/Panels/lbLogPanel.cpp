#include "lbLogPanel.h"

namespace Lambix
{
    lbLogPanel::lbLogPanel(const std::shared_ptr<lbImGuiSink> &sink) : mSink(sink)
    {
    }

    void lbLogPanel::OnImGuiRender()
    {
        if (!mSink)
            return;

        ImGui::Begin("Log");

        // 控制栏
        if (ImGui::Button("Clear"))
            mSink->Clear();
        ImGui::SameLine();
        ImGui::Checkbox("Auto Scroll", &mStyle.auto_scroll);

        // 日志列表
        ImGui::Separator();
        ImGui::BeginChild("log_list");

        auto logs = mSink->GetLogs(false);
        for (const auto &log : logs)
        {
            // 设置颜色
            const ImVec4 *color = &mStyle.info_color;
            switch (log.level)
            {
            case spdlog::level::trace:
                color = &mStyle.trace_color;
                break;
            case spdlog::level::info:
                color = &mStyle.info_color;
                break;
            case spdlog::level::warn:
                color = &mStyle.warn_color;
                break;
            case spdlog::level::err:
                color = &mStyle.error_color;
                break;
            case spdlog::level::critical:
                color = &mStyle.critical_color;
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
        if (mStyle.auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }

} // namespace Lambix
