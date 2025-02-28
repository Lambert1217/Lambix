/**
 ***************************************************************
 * @file            : lbLog.cpp
 * @author          : Lambert
 * @brief           : 基于spdlog的日志系统
 * @attention       : None
 * @data            : 2024/8/20
 ***************************************************************
 */
//

#pragma once

#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <mutex>

namespace Lambix
{

	class lbLog
	{
	public:
		// 初始化日志系统 (控制台日志开关, ImGui日志开关)
		static void Init(bool console_enable = true, bool imgui_enable = false);

		// 动态控制日志输出目标
		static void EnableConsole(bool enable);
		static void EnableImGui(bool enable);

		static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
		static std::shared_ptr<class lbImGuiSink> s_ImGuiSink; // 前向声明
		static std::mutex s_Mutex;
	};
}

// 日志系统输出宏
#define LOG_TRACE(...) ::Lambix::lbLog::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Lambix::lbLog::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Lambix::lbLog::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Lambix::lbLog::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Lambix::lbLog::GetLogger()->critical(__VA_ARGS__)

// 断言
#ifdef LAMBIX_DEBUG
#define LOG_ASSERT(x, ...)                                                                              \
	{                                                                                                   \
		if (!(x))                                                                                       \
		{                                                                                               \
			LOG_CRITICAL("Assertion Failed at {0}:{1}, Assertion Info as Follow:", __FILE__, __LINE__); \
			LOG_CRITICAL(__VA_ARGS__);                                                                  \
			__debugbreak();                                                                             \
		}                                                                                               \
	}
#else
#define LOG_ASSERT(x, ...)
#endif