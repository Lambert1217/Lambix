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

#include "Core/Base/lbLog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Core/UI/Imgui/lbLogUI.h"

namespace Lambix
{

	std::shared_ptr<spdlog::logger> lbLog::s_Logger;
	std::shared_ptr<lbImGuiSink> lbLog::s_ImGuiSink;
	std::mutex lbLog::s_Mutex;

	void lbLog::Init(bool console_enable, bool imgui_enable)
	{
		std::vector<spdlog::sink_ptr> sinks;

		// 控制台日志
		if (console_enable)
		{
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_sink->set_pattern("[%n][%T]%^[%l]%$: %v");
			sinks.push_back(console_sink);
		}

		// ImGui日志
		if (imgui_enable)
		{
			s_ImGuiSink = std::make_shared<lbImGuiSink>();
			lbLogUI::Init(s_ImGuiSink);
			sinks.push_back(s_ImGuiSink);
		}

		s_Logger = std::make_shared<spdlog::logger>("Lambix", begin(sinks), end(sinks));
		s_Logger->set_level(spdlog::level::trace);

		LOG_INFO("Log System Initialized (Console: {}, ImGui: {})",
				 console_enable ? "Enabled" : "Disabled",
				 imgui_enable ? "Enabled" : "Disabled");
	}

	void lbLog::EnableConsole(bool enable)
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		auto &sinks = s_Logger->sinks();

		if (enable)
		{
			// 检查是否已存在控制台sink
			auto it = std::find_if(sinks.begin(), sinks.end(), [](const spdlog::sink_ptr &sink)
								   { return dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(sink.get()) != nullptr; });

			if (it == sinks.end())
			{
				auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
				console_sink->set_pattern("[%n][%T]%^[%l]%$: %v");
				sinks.push_back(console_sink);
			}
			LOG_INFO("Console Log Enabled");
		}
		else
		{
			// 移除所有控制台sink
			sinks.erase(std::remove_if(sinks.begin(), sinks.end(), [](const spdlog::sink_ptr &sink)
									   { return dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(sink.get()) != nullptr; }),
						sinks.end());
			LOG_INFO("Console Log Disabled");
		}
	}

	void lbLog::EnableImGui(bool enable)
	{
		std::lock_guard<std::mutex> lock(s_Mutex);
		auto &sinks = s_Logger->sinks();

		if (enable && !s_ImGuiSink)
		{
			s_ImGuiSink = std::make_shared<lbImGuiSink>();
			lbLogUI::Init(s_ImGuiSink);
			sinks.push_back(s_ImGuiSink);
			LOG_INFO("ImGui Log Enabled");
		}
		else if (!enable && s_ImGuiSink)
		{
			sinks.erase(std::remove(sinks.begin(), sinks.end(), s_ImGuiSink), sinks.end());
			s_ImGuiSink.reset();
			LOG_INFO("ImGui Log Disabled");
		}
	}

}