/**
 * @file lbPropertyPanel.h
 * @author 刘亚奇 (1904310303@qq.com)
 * @brief 属性面板
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include "lbPanel.h"

namespace Lambix
{
    class lbPropertyPanel : public lbPanel
    {
    public:
        lbPropertyPanel();
        ~lbPropertyPanel() override;

        using Ptr = std::shared_ptr<lbPropertyPanel>;
        static Ptr Create()
        {
            return std::make_shared<lbPropertyPanel>();
        }

        enum class PropertyType
        {
            None = 0,
            Entity,
            Asset
        };

        void OnImGuiRender() override;

    private:
        void DrawProperty(lbEntity *entity);

        void DrawAssetProperty();

        void DrawTexture2DAsset(const lbTexture2DAsset::Ptr &texture);

        void DrawBasicMaterial(const lbBasicMaterial::Ptr &material);

        void OnEntitySeleted(const lbEvent::Ptr &event);

        void OnAssetSeleted(const lbEvent::Ptr &event);

    private:
        void *any{nullptr};
        PropertyType mType{PropertyType::None};

        // 资产属性编辑相关
        std::filesystem::path mAssetPath;
        lbAssetManager::Ptr mAssetManager{nullptr};
    };
} // namespace Lambix
