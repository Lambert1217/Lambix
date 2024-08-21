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

extern Lambix::lbApplication *Lambix::CreateApplication();

// 程序的入口
int main(int argc, char **argv)
{
	// 初始化日志
	Lambix::lbLog::init();

	// 窗口创建
	auto app = Lambix::CreateApplication();
	// 窗口运行
	app->run();

	return 0;
}
