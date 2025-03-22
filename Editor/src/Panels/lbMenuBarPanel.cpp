#include "lbMenuBarPanel.h"

namespace Lambix
{
    void lbMenuBarPanel::OnImGuiRender()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    lbApplication::GetInstance().Quit();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
} // namespace Lambix
