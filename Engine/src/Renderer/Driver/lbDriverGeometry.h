/**
 * @file lbDriverGeometry.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbDriverAttribute.h"
#include "lbDriverBindingState.h"
#include "lbDriverInfo.h"

namespace Lambix
{
    class lbDriverGeometries
    {
    public:
        lbDriverGeometries(
            const lbDriverAttributes::Ptr &attributes,
            const lbDriverInfo::Ptr &info,
            const lbDriverBindingStates::Ptr &bindingStates);
        ~lbDriverGeometries();

        using Ptr = std::shared_ptr<lbDriverGeometries>;
        static Ptr Create(const lbDriverAttributes::Ptr &attributes,
                          const lbDriverInfo::Ptr &info,
                          const lbDriverBindingStates::Ptr &bindingStates)
        {
            return std::make_shared<lbDriverGeometries>(attributes, info, bindingStates);
        }

        void OnGeometryDispose(const lbEvent::Ptr &event);

        lbGeometry::Ptr Get(const lbGeometry::Ptr &geometry);

        void OnUpdate(const lbGeometry::Ptr &geometry);

    private:
        lbDriverAttributes::Ptr mAttributes{nullptr};
        lbDriverInfo::Ptr mInfo{nullptr};

        // VAO相关
        lbDriverBindingStates::Ptr mBindingStates{nullptr};

        // 控制每个geometry只记录一次
        std::unordered_map<lbUUID, bool> mGeometries{};
    };
} // namespace Lambix
