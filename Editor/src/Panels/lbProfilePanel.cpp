#include "lbProfilePanel.h"

namespace Lambix
{
    void lbProfilePanel::OnImGuiRender()
    {
        ImGui::Begin("Profile");

        auto boldFont = ImGui::GetIO().Fonts->Fonts[1];
        float ColumnWidth0 = ImGui::GetContentRegionAvail().x * 0.6f;

        // Info
        if (mRendererSystem)
        {
            static bool rendererInfoOpen = true;
            ImGui::PushFont(boldFont);
            rendererInfoOpen = ImGui::TreeNodeEx((const void *)typeid(lbDriverInfo).hash_code(),
                                                 ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, "Renderer Info");
            ImGui::PopFont();
            ImGui::Separator();

            if (rendererInfoOpen)
            {
                ImGui::Columns(2, "renderer_info_fps", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("FPS: ");
                ImGui::NextColumn();
                ImGui::Text("%d", mRendererSystem->mInfo->mRender.FPS);
                ImGui::Columns(1);
                ImGui::TreePop();
            }
        }

        // lbProfileResults : Timer的计时结果
        static bool profileResultsOpen = true;
        ImGui::PushFont(boldFont);
        profileResultsOpen = ImGui::TreeNodeEx((const void *)typeid(lbProfileResults).hash_code(),
                                               ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, "Profile Results");
        ImGui::PopFont();
        ImGui::Separator();

        if (profileResultsOpen)
        {
            for (auto &result : lbProfileResults::Get()->GetResults())
            {
                std::string pre = "ProfileResults";
                ImGui::Columns(2, (pre + result.first).c_str(), false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("%s: ", result.first.c_str());
                ImGui::NextColumn();
                ImGui::Text("%.3fms", result.second);
                ImGui::Columns(1);
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }
} // namespace Lambix
