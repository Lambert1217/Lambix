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
                if (ImGui::MenuItem("New Project"))
                {
                    NewPorject();
                }
                if (ImGui::MenuItem("Open Project"))
                {
                    OpenProject(lbFileDiologs::OpenFile("Lambix Project(*.lproj)\0*.lproj\0"));
                }
                if (ImGui::MenuItem("Save Project"))
                {
                    SaveProject();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void lbMenuBarPanel::NewPorject()
    {
        std::filesystem::path p = lbFileDiologs::SaveFile("Lambix Project(*.lproj)\0*.lproj\0");
        if (p.string().empty())
            return;
        lbProjectSpecification spec;
        spec.mName = p.filename().string();
        spec.mPath = p.parent_path();
        lbProject::Create(spec)->Serialize();
    }

    void lbMenuBarPanel::OpenProject(const std::filesystem::path &path)
    {
        SaveProject();
        mCurrentProject.reset(new lbProject());
        mCurrentProject->Deserialize(path);
        // 发出打开项目事件
        auto event = lbEventPool::Get()->Acquire();
        event->Set("OpenProject", this, mCurrentProject.get());
        lbEventDispatcher::Get()->dispatchEvent(event);
    }

    void lbMenuBarPanel::SaveProject()
    {
        if (mCurrentProject)
        {
            mCurrentProject->Serialize();
        }
    }
} // namespace Lambix
