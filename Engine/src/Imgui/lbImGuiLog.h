/**
 * @file lbImGuiLog.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

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
} // namespace Lambix
