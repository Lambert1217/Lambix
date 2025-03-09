/**
 * @file lbEventPool.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 线程安全的事件对象资源池，支持对象的复用和自动回收
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbEvent.h"
#include "Utils/lbSingleton.h"
#include "Log/lbLog.h"

namespace Lambix
{
    class lbEventPool : public lbSingleton<lbEventPool>
    {
    public:
        // 资源池配置
        struct Config
        {
            size_t init_size = 10;    // 初始预创建数量
            size_t max_size = 1000;   // 最大事件数量
            size_t timeout_ms = 2000; // 获取超时时间(毫秒)
        };

        lbEventPool()
        {
            Initialize();
        }

        virtual ~lbEventPool() override
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            while (!m_pool.empty())
            {
                delete m_pool.front();
                m_pool.pop();
            }
        }

        void Initialize(const Config &config = {})
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_config = config;

            for (size_t i = 0; i < m_config.init_size; ++i)
            {
                m_pool.push(CreateNewEvent());
            }
        }

        lbEvent::Ptr Acquire()
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            // 等待可用资源或超时
            if (m_cv.wait_for(lock,
                              std::chrono::milliseconds(m_config.timeout_ms),
                              [this]
                              { return !m_pool.empty(); }))
            {
                auto event = m_pool.front();
                m_pool.pop();
                return WrapEvent(event);
            }

            // 尝试创建新事件（不超过最大值）
            if (m_active_count < m_config.max_size)
            {
                return WrapEvent(CreateNewEvent());
            }

            throw std::runtime_error("Acquire event timeout");
        }

    private:
        Config m_config;
        std::queue<lbEvent *> m_pool;
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::atomic<size_t> m_active_count{0};

        // 创建新事件对象
        lbEvent *CreateNewEvent()
        {
            static std::atomic<size_t> counter{0};
            m_active_count++;
            return new lbEvent();
        }

        // 包装事件对象到智能指针
        lbEvent::Ptr WrapEvent(lbEvent *event)
        {
            // 重置事件状态
            event->Set("lbEvent", nullptr, nullptr);

            return lbEvent::Ptr(event,
                                [this](lbEvent *e)
                                { ReleaseEvent(e); });
        }

        // 事件回收处理
        void ReleaseEvent(lbEvent *event)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_pool.size() < m_config.max_size)
            {
                m_pool.push(event);
                m_cv.notify_one();
            }
            else
            {
                delete event;
                m_active_count--;
            }
        }
    };
} // namespace Lambix
