#include "lbAssetsBrowserPanel.h"

namespace Lambix
{
    lbAssetsBrowserPanel::lbAssetsBrowserPanel(const lbAssetManager::Ptr &manager)
    {
        SetContext(manager);
    }

    void lbAssetsBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Assets Browser");

        if (mAssetManager)
        {
            if (mCurrentPath != mAssetManager->GetRoot())
            {
                if (ImGui::Button("Back to Parent Directory"))
                {
                    mCurrentPath = mCurrentPath.parent_path();
                }
            }

            for (auto &directoryEntry : std::filesystem::directory_iterator(mCurrentPath))
            {
                auto &path = directoryEntry.path();
                std::string filenameStr = path.filename().string();
                if (directoryEntry.is_directory())
                {
                    if (ImGui::Button(filenameStr.c_str()))
                    {
                        mCurrentPath = path;
                    }
                }
                else
                {
                    ImGui::Text(filenameStr.c_str());
                }
            }
        }

        ImGui::End();
    }

    void lbAssetsBrowserPanel::SetContext(const lbAssetManager::Ptr &manager)
    {
        mAssetManager = manager;
        mCurrentPath = manager->GetRoot();
    }

} // namespace Lambix
