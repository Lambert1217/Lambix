#include "lbAssetsBrowserPanel.h"
#include "Utils/lbFileDiologs.h"

namespace Lambix
{
    constexpr const char *const AssetsFilter = "Texture2D (*.ltex)\0*.ltex\0";
    static ImTextureID FileIcon;
    static ImTextureID DirectoryIcon;

    lbAssetsBrowserPanel::lbAssetsBrowserPanel(const lbAssetManager::Ptr &manager)
    {
        SetContext(manager);
    }

    void lbAssetsBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Assets Browser");

        if (mAssetManager)
        {
            ImGui::Text("%s", mCurrentPath.string().c_str());

            if (ImGui::Button("Create Asset"))
            {
                CreateAsset(lbFileDiologs::SaveFile(AssetsFilter));
            }
            if (mCurrentPath != mAssetManager->GetRoot())
            {
                if (ImGui::Button("<-- Back"))
                {
                    mCurrentPath = mCurrentPath.parent_path();
                }
            }

            // 布局参数
            const float button_size = 128.0f;
            const float spacing = 16.0f;                              // 元素间距
            const float text_height = ImGui::CalcTextSize("A").y * 2; // 预留两行文本高度

            // 获取可用区域宽度
            float available_width = ImGui::GetContentRegionAvail().x;
            int items_per_row = static_cast<int>(available_width / (button_size + spacing));

            if (items_per_row < 1)
                items_per_row = 1;

            ImGuiStyle &style = ImGui::GetStyle();
            ImVec2 initial_cursor_pos = ImGui::GetCursorScreenPos();
            float current_x = initial_cursor_pos.x;
            float current_y = initial_cursor_pos.y;

            for (auto &directoryEntry : std::filesystem::directory_iterator(mCurrentPath))
            {
                const auto &path = directoryEntry.path();
                const std::string filenameStr = path.filename().string();

                ImGui::PushID(filenameStr.c_str());

                // 计算是否需要换行
                if ((current_x - initial_cursor_pos.x) + button_size > available_width)
                {
                    current_x = initial_cursor_pos.x;
                    current_y += button_size + text_height + spacing;
                    ImGui::SetCursorScreenPos(ImVec2(current_x, current_y));
                }

                // TODO：修改纹理为Icon
                ImTextureID textureID = directoryEntry.is_directory() ? DirectoryIcon : FileIcon;

                // 创建带纹理的按钮
                ImGui::SetCursorScreenPos(ImVec2(current_x, current_y));
                if (ImGui::ImageButton(textureID, ImVec2(button_size, button_size)))
                {
                    if (directoryEntry.is_directory())
                    {
                        mCurrentPath = path;
                    }
                    else if (path.extension().string() == ".ltex")
                    {
                        auto event = lbEventPool::Get()->Acquire();
                        event->Set("AssetSeleted", this, (void *)&path);
                        lbEventDispatcher::Get()->dispatchEvent(event);
                    }
                }
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Text("%s", filenameStr.c_str());
                    ImGui::EndTooltip();
                }
                // 文件名显示
                ImGui::SetCursorScreenPos(ImVec2(current_x, current_y + button_size + style.ItemSpacing.y));
                ImGui::BeginChild("TextArea", ImVec2(button_size + spacing / 2, text_height), false);
                ImGui::Text("%s", filenameStr.c_str());
                ImGui::EndChild();

                // 更新下一个元素位置
                current_x += button_size + spacing;
                ImGui::PopID();
            }
        }

        ImGui::End();
    }

    void lbAssetsBrowserPanel::SetContext(const lbAssetManager::Ptr &manager)
    {
        mAssetManager = manager;
        mCurrentPath = manager->GetRoot();
        // 加载两个图标
        FileIcon = (ImTextureID)(uintptr_t)std::static_pointer_cast<lbTexture2DAsset>(mAssetManager->Load("..\\Assets\\Textures\\FileIcon.ltex", true))->GetRendererID();
        DirectoryIcon = (ImTextureID)(uintptr_t)std::static_pointer_cast<lbTexture2DAsset>(mAssetManager->Load("..\\Assets\\Textures\\DirectoryIcon.ltex", true))->GetRendererID();
    }

    void lbAssetsBrowserPanel::CreateAsset(const std::filesystem::path &p)
    {
        // 拓展名
        if (p.string().empty())
            return;
        auto extension = p.extension().string().substr(1);
        // 2D纹理
        if (extension == "ltex")
        {
            // TODO: 修改内部资源的路径
            auto defaultSource = std::static_pointer_cast<lbTextureSourceAsset>(mAssetManager->Load("..\\Assets\\Textures\\1_1White.png", true));
            lbTexture2DAsset::Ptr texture2d = lbTexture2DAsset::Create(defaultSource);
            texture2d->Serialize(p, lbSerializationFormat::Yaml);
        }
    }

} // namespace Lambix
