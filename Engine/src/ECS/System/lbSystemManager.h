/**
 * @file lbSystemManager.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 系统管理器（基于multiset的优先级排序）
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbSystem.h"
#include "Log/lbLog.h"

namespace Lambix
{
    class SystemComparator
    {
    public:
        bool operator()(const lbSystem *a, const lbSystem *b) const
        {
            // 先按优先级排序，优先级相同则按地址排序（保持插入顺序）
            return a->GetPriority() < b->GetPriority();
        }
    };

    class lbSystemManager
    {
    public:
        ~lbSystemManager();

        // 安全创建系统
        template <typename T, typename... Args>
        T *CreateSystem(Args &&...args)
        {
            static_assert(std::is_base_of_v<lbSystem, T>, "T must inherit from lbSystem");

            auto system = std::make_unique<T>(std::forward<Args>(args)...);
            T *ptr = system.get();

            // 名称唯一性检查
            if (m_SystemMap.contains(ptr->GetName()))
            {
                LOG_ERROR("System name conflict: {}", ptr->GetName());
                return nullptr;
            }

            m_Systems.insert(ptr);
            m_SystemMap[ptr->GetName()] = ptr;
            m_OwnedSystems.push_back(std::move(system));
            return ptr;
        }

        void OnUpdate(lbTimestep ts);
        void OnEvent(Event &event);

        // 按名称获取系统
        lbSystem *GetSystem(const std::string &name);

        // 清空所有系统
        void Clear();

    private:
        std::multiset<lbSystem *, SystemComparator> m_Systems;
        std::unordered_map<std::string, lbSystem *> m_SystemMap;
        std::vector<std::unique_ptr<lbSystem>> m_OwnedSystems;
    };
} // namespace Lambix
