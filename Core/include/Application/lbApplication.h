/**
 ***************************************************************
 * @file            : lbApplication.h
 * @author          : Lambert
 * @brief           : 控制程序循环
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{

	class lbApplication
	{
	 public:
		lbApplication();
		virtual ~lbApplication() = default;

		/**
		 * @brief 程序执行
		 */
		void run();

		/**
		 * @brief 程序退出
		 */
		void quit();

		/**
		 * 获取程序单例
		 * @return
		 */
		inline static lbApplication& GetInstance() { return *s_lbApplication; }

	 private:
		static lbApplication* s_lbApplication; // 应用类单例
	};

	/**
	 * @brief 创建程序,由使用者实现
	 * @return
	 */
	lbApplication* CreateApplication();

} // Lambix
