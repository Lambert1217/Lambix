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

namespace Lambix
{

	class lbLog
	{
	public:
		/**
		 * @brief 日志系统初始化
		 *
		 */
		static void init();

		/**
		 * @brief Get the Logger object
		 *
		 * @return std::shared_ptr<spdlog::logger>&
		 */
		inline static std::shared_ptr<spdlog::logger> &GetLogger()
		{
			return s_Logger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

} // Lambix

// 日志系统输出宏
#define LOG_TRACE(...) ::Lambix::lbLog::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Lambix::lbLog::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Lambix::lbLog::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Lambix::lbLog::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Lambix::lbLog::GetLogger()->critical(__VA_ARGS__)

// 断言
#ifdef LAMBIX_DEBUG
#define LOG_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			LOG_CRITICAL("Assertion Failed({0}:{1})\n{2}", __FILE__ , __LINE__ , __VA_ARGS__); \
			__debugbreak();                                  \
		}                                                    \
	}
#else
#define LOG_ASSERT(x, ...)
#endif