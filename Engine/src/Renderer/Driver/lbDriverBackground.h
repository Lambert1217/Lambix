/**
 * @file lbDriverBackground.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 管理渲染的背景，如清理颜色，天空盒
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "ECS/lbEntity.h"
#include "ECS/lbScene.h"

namespace Lambix
{
    class lbDriverBackground
    {
    public:
        lbDriverBackground(lbScene *scene);
        ~lbDriverBackground();

        using Ptr = std::shared_ptr<lbDriverBackground>;
        static Ptr Create(lbScene *scene)
        {
            return std::make_shared<lbDriverBackground>(scene);
        }

        void OnUpdate(lbTimestep ts);

        void SetClearColor(const glm::vec4 &color) { mClearColor = color; }

    private:
        glm::vec4 mClearColor = {0.3f, 0.3f, 0.3f, 1.0f};
        std::shared_ptr<lbEntity> mSkybox{nullptr};
        lbScene *mScene{nullptr};
    };
} // namespace Lambix
