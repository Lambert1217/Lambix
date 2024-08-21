/**
 ***************************************************************
 * @file            : lbLog.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/20
 ***************************************************************
 */
//

#include "Debug/lbLog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Lambix
{
	// 静态变量在类外部定义
	std::shared_ptr<spdlog::logger> lbLog::s_Logger;

	void lbLog::init()
	{
		// 设置日志输出格式
		spdlog::set_pattern("[%n][%T] %^[%l]%$: %v");

		// 设置logger的名称和等级
		s_Logger = spdlog::stdout_color_mt("Lambix");
		s_Logger->set_level(spdlog::level::trace);

		LOG_INFO("Log initialization successful");
		LOG_INFO("Welcome to Lambix Engine!");
	}
} // Lambix