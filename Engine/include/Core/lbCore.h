/**
 ***************************************************************
 * @file            : lbCore.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

// 处理事件大类枚举，使得可以组合
#define BIT(x) (1 << x)

// 绑定函数
#define LB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
