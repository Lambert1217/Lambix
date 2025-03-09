/**
 * @file lbEvent.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 引擎的事件系统
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Utils/lbSingleton.h"

namespace Lambix
{
    /**
     * @brief 事件系统，事件主体
     *
     */
    struct lbEvent
    {
        std::string m_EventName{"lbEvent"}; // 事件名称
        void *m_Emitter{nullptr};           // 事件发出者的指针
        void *m_UserData{nullptr};          // 用户可以用来传递一些信息

        // 构造和析构函数
        lbEvent() noexcept = default;
        ~lbEvent() noexcept = default;

        /**
         * @brief 设置参数
         *
         * @param name
         * @param emitter
         * @param data
         */
        void Set(const std::string &name, void *emitter, void *data = nullptr);

        using Ptr = std::shared_ptr<lbEvent>;
    };

    class lbEventDispatcher : public lbSingleton<lbEventDispatcher>
    {
    public:
        /**
         * @brief For class::function
         *       可以表示一个类内函数，传入模板为类名
         * @tparam T
         */
        template <typename T>
        using TypedFunctionPointer = void (T::*)(const lbEvent::Ptr &);

        /**
         * @brief 事件函数别名
         *
         */
        using EventFunction = std::function<void(const lbEvent::Ptr &)>;

        /**
         * @brief 事件监听器
         *
         */
        struct lbListener
        {
            lbListener() = default;
            ~lbListener()
            {
                if (m_FunctionPointerDescriptor.m_Addr)
                {
                    free(m_FunctionPointerDescriptor.m_Addr);
                }
            }

            using Ptr = std::shared_ptr<lbListener>;
            static Ptr Create() { return std::make_shared<lbListener>(); }

            /**
             * @brief 函数指针描述器，为了解决函数指针不能直接比较的问题
             *
             */
            struct FunctionPointerDescriptor
            {
                void *m_Addr{nullptr}; // 函数指针地址的指针
                uint32_t m_Size{0};

                bool operator==(const FunctionPointerDescriptor &other) const
                {
                    if (other.m_Size != m_Size)
                    {
                        return false;
                    }
                    if (memcmp(m_Addr, other.m_Addr, m_Size) != 0)
                    {
                        return false;
                    }
                    return true;
                }
            };

            /**
             * @brief 构造函数指针描述器
             *
             * @tparam T
             * @param functionPointer
             * @return FunctionPointerDescriptor
             */
            template <typename T>
            static FunctionPointerDescriptor buildFunctionPointer(TypedFunctionPointer<T> functionPointer) noexcept
            {
                // 计算本函数指针的大小
                uint32_t size = sizeof(TypedFunctionPointer<T>);
                // 分配一片内存
                void *ptr = malloc(size);
                // placement New 先分配了一块内存，然后通过placementNew调用了其构造函数/默认构造
                new (ptr) TypedFunctionPointer<T>(functionPointer);

                lbListener::FunctionPointerDescriptor res;
                res.m_Addr = ptr;
                res.m_Size = size;

                return res;
            }

            // 监听者
            void *m_ListenerObject{nullptr};

            // 函数指针描述器，用于比较函数指针
            FunctionPointerDescriptor m_FunctionPointerDescriptor{};

            // 函数指针, 调用时使用
            EventFunction m_EventFunction{nullptr};
        };

        /**
         * @brief 静态方法比较两个监听器是否相同
         *
         * @param l0
         * @param l1
         * @return true
         * @return false
         */
        static bool listenerIsEqual(const lbListener::Ptr &l0, const lbListener::Ptr &l1)
        {
            return l0->m_ListenerObject == l1->m_ListenerObject && l0->m_FunctionPointerDescriptor == l1->m_FunctionPointerDescriptor;
        }

        using ListenerQueue = std::vector<lbListener::Ptr>;

        /**
         * @brief 添加事件监听器
         *
         * @tparam T 监听者的类型
         * @param name 监听事件的名称
         * @param listenerObject 监听者的指针
         * @param functionPointer 监听者的类内函数
         */
        template <typename T>
        void addEventListener(const std::string &name, T *listenerObject, TypedFunctionPointer<T> functionPointer);

        /**
         * @brief 移除事件监听器
         *
         * @tparam T 监听者的类型
         * @param name 监听事件的名称
         * @param listenerObject 监听者的指针
         * @param functionPointer 监听者的类内函数
         */
        template <typename T>
        void removeEventListener(const std::string &name, T *listenerObject, TypedFunctionPointer<T> functionPointer);

        /**
         * @brief 事件分发，一旦派发，立即处理
         *
         * @param event
         */
        void dispatchEvent(const lbEvent::Ptr &event);

    protected:
        /**
         * @brief 每一种事件对应一个监听者队列
         *
         */
        std::unordered_map<std::string, ListenerQueue> m_Listeners;
    };

    template <typename T>
    inline void lbEventDispatcher::addEventListener(const std::string &name, T *listenerObject, TypedFunctionPointer<T> functionPointer)
    {
        auto queueIter = m_Listeners.find(name);
        if (queueIter == m_Listeners.end())
        {
            queueIter = (m_Listeners.insert(std::make_pair(name, ListenerQueue()))).first;
        }

        auto &listenerQueue = queueIter->second;

        // 构建监听器
        lbListener::Ptr listener = lbListener::Create();
        listener->m_ListenerObject = listenerObject;
        listener->m_FunctionPointerDescriptor = lbListener::buildFunctionPointer(functionPointer);
        listener->m_EventFunction = std::bind(functionPointer, listenerObject, std::placeholders::_1);

        auto listenerIter = std::find_if(listenerQueue.begin(), listenerQueue.end(),
                                         [&](const lbListener::Ptr &l)
                                         {
                                             return lbEventDispatcher::listenerIsEqual(listener, l);
                                         });
        if (listenerIter != listenerQueue.end())
        {
            return;
        }

        listenerQueue.push_back(listener);
    }

    template <typename T>
    inline void lbEventDispatcher::removeEventListener(const std::string &name, T *listenerObject, TypedFunctionPointer<T> functionPointer)
    {
        auto queueIter = m_Listeners.find(name);
        if (queueIter == m_Listeners.end())
        {
            return;
        }

        auto &listenerQueue = queueIter->second;

        // 构建监听器
        lbListener::Ptr listener = lbListener::Create();
        listener->m_ListenerObject = listenerObject;
        listener->m_FunctionPointerDescriptor = lbListener::buildFunctionPointer(functionPointer);
        listener->m_EventFunction = std::bind(functionPointer, listenerObject, std::placeholders::_1);

        auto listenerIter = std::find_if(listenerQueue.begin(), listenerQueue.end(),
                                         [&](const lbListener::Ptr &l)
                                         {
                                             return lbEventDispatcher::listenerIsEqual(listener, l);
                                         });
        if (listenerIter != listenerQueue.end())
        {
            listenerQueue.erase(listenerIter);
        }
    }
} // namespace Lambix
