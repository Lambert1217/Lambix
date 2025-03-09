/**
 * @file lbSingleton.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 单例基类，可以继承该类轻松实现单例
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

namespace Lambix
{
    template <typename T>
    class lbSingleton
    {
    public:
        // 获取单例实例
        static std::shared_ptr<T> Get()
        {
            static std::shared_ptr<T> s_Instance = nullptr;
            static std::once_flag s_Once;
            std::call_once(s_Once, []()
                           { s_Instance = std::make_shared<T>(); });
            return s_Instance;
        }
        // 删除拷贝构造和赋值运算符
        lbSingleton(const lbSingleton &) = delete;
        lbSingleton &operator=(const lbSingleton &) = delete;

    protected:
        lbSingleton() = default;
        virtual ~lbSingleton() = default;
    };
} // namespace Lambix
