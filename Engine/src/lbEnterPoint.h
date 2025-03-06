/**
 ***************************************************************
 * @file            : lbEnterPoint.h
 * @author          : Lambert
 * @brief           : 程序入口
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//
#pragma once

#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX

extern Lambix::lbApplication *Lambix::CreateApplication();
// 程序的入口
int main(int argc, char **argv)
{
	// 初始化日志
	Lambix::lbLog::Init(true, true);

	// 程序创建
	auto app = Lambix::CreateApplication();
	// 窗口运行
	app->Run();

	return 0;
}
#endif
