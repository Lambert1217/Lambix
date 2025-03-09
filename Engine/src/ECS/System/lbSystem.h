/**
 * @file lbSystem.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 系统基类
 * 关于系统更新的优先级问题，暂定如下
 *      默认的     0
 *      Transform 1
 *      Camera    2
 *      Light     3
 *      Render    4
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "Utils/lbTimestep.h"

namespace Lambix
{
    class lbScene;
    class lbSystem
    {
    public:
        explicit lbSystem(lbScene *scene, uint32_t priority = 0, const std::string &name = "System")
            : m_Scene(scene), m_Priority(priority), m_Name(name) {}
        virtual ~lbSystem() = default;

        virtual void Init() {}
        virtual void OnUpdate(lbTimestep ts) {}

        const std::string &GetName() const { return m_Name; }
        uint32_t GetPriority() const { return m_Priority; }

    protected:
        lbScene *m_Scene;   // 所属场景的指针
        std::string m_Name; // 系统的名称

        /**
         * @brief 用于控制不同组件的更新优先级  “从低到高”
         */
        uint32_t m_Priority;
    };
} // namespace Lambix
