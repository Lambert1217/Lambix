#include "lbImGuiLog.h"

namespace Lambix
{
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
} // namespace Lambix
