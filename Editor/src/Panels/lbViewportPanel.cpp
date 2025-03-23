#include "lbViewportPanel.h"

namespace Lambix
{
    lbViewportPanel::lbViewportPanel(const std::shared_ptr<lbScene> &secne)
        : mScene(secne)
    {
    }

    void lbViewportPanel::OnImGuiRender()
    {
        auto mFrameBuffer = mScene->GetFrameBuffer();
        if (!mFrameBuffer)
        {
            return;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");

        // 视口渲染
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        const auto &frameBufferSpec = mFrameBuffer->GetSpecification();
        if ((uint32_t)viewportPanelSize.x != frameBufferSpec.width || (uint32_t)viewportPanelSize.y != frameBufferSpec.height)
        {
            // 发出事件
            auto event = lbEventPool::Get()->Acquire();
            event->Set("ViewportResize", this, &viewportPanelSize);
            lbEventDispatcher::Get()->dispatchEvent(event);
        }
        static ImTextureID TextureID = (ImTextureID)(uintptr_t)mFrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image(TextureID, viewportPanelSize, ImVec2{0, 1}, ImVec2{1, 0});

        // 发出视口获取焦点事件
        if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
        {
            auto event = lbEventPool::Get()->Acquire();
            event->Set("ViewportReadyForCameraControl", this, nullptr);
            lbEventDispatcher::Get()->dispatchEvent(event);
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace Lambix
