#include "lbSceneHierarchyPanel.h"

namespace Lambix
{
    void lbSceneHierarchyPanel::OnImGuiRender()
    {
        if (!mContext)
            return;
        ImGui::Begin("Scene Hierarchy");
        for (auto &it : mContext->m_EntityMap)
        {
            if (it.second->GetParent())
            {
                continue;
            }
            DrawEntityNode(it.second);
        }
        ImGui::End();
    }

    void lbSceneHierarchyPanel::DrawEntityNode(const std::shared_ptr<lbEntity> &entity)
    {
        auto &IdComp = entity->GetComponent<lbIdentityComponent>();

        ImGuiTreeNodeFlags flags = (mSeletedEntity == entity ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool isOpen = ImGui::TreeNodeEx((void *)IdComp.m_UUID, flags, IdComp.m_Name.c_str());

        if (ImGui::IsItemClicked())
        {
            mSeletedEntity = entity;
            // 事件派发
            auto event = lbEventPool::Get()->Acquire();
            event->Set("EntitySeleted", this, entity.get());
            lbEventDispatcher::Get()->dispatchEvent(event);
        }

        if (isOpen)
        {
            // 获取子节点并递归绘制
            auto children = entity->GetChildren();
            for (const auto &childEntity : children)
            {
                DrawEntityNode(childEntity);
            }
            ImGui::TreePop();
        }
    }
} // namespace Lambix
