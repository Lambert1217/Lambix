/**
 ***************************************************************
 * @file            : lbTimestep.h
 * @author          : Lambert
 * @brief           : lbTimestep类负责表示和管理时间步长
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{
	class lbTimestep
	{
	 public:
		/**
		* @brief 构造函数,初始化时间步长默认为0秒
		*
		* @param time 时间步长,单位秒
		*/
		lbTimestep(float time = 0.0f) : m_Time(time) {}

		/**
		 * @brief 直接转换为浮点数值获取时间步长,单位秒
		 */
		operator float() const { return m_Time; }

		/**
		 * @brief 获取时间步长,单位秒
		 *
		 * @return 时间步长值,单位秒
		 */
		float GetSeconds() const { return m_Time; }

		/**
		 * @brief 获取时间步长,单位毫秒
		 *
		 * @return 时间步长值,单位毫秒
		 */
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	 private:
		float m_Time;
	};
}
