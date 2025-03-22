/**
 * @file lbPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief UI面板基类
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "imgui.h"
#include "lbEngine.h"

namespace Lambix
{
    class lbPanel
    {
    public:
        virtual ~lbPanel() = default;

        virtual void OnImGuiRender() = 0;

        using Ptr = std::shared_ptr<lbPanel>;
    };

    /**
     * @brief Hex转 ImVec4
     *
     * @param value
     * @return ImVec4
     */
    ImVec4 ToImVec4(uint32_t value);
} // namespace Lambix
