#include "lbPropertyPanel.h"
#include "glm/gtc/type_ptr.hpp"
#include "lbAssetsBrowserPanel.h"

namespace Lambix
{
    lbPropertyPanel::lbPropertyPanel()
    {
        lbEventDispatcher::Get()->addEventListener<lbPropertyPanel>("EntitySeleted", this, &lbPropertyPanel::OnEntitySeleted);
        lbEventDispatcher::Get()->addEventListener<lbPropertyPanel>("AssetSeleted", this, &lbPropertyPanel::OnAssetSeleted);
    }

    lbPropertyPanel::~lbPropertyPanel()
    {
        lbEventDispatcher::Get()->removeEventListener<lbPropertyPanel>("EntitySeleted", this, &lbPropertyPanel::OnEntitySeleted);
        lbEventDispatcher::Get()->removeEventListener<lbPropertyPanel>("AssetSeleted", this, &lbPropertyPanel::OnAssetSeleted);
    }

    void lbPropertyPanel::OnImGuiRender()
    {
        ImGui::Begin("Properties");
        switch (mType)
        {
        case PropertyType::None:
            break;
        case PropertyType::Entity:
            DrawProperty(static_cast<lbEntity *>(any));
            break;
        case PropertyType::Asset:
            DrawAssetProperty();
            break;
        default:
            break;
        }
        ImGui::End();
    }

    void lbPropertyPanel::DrawProperty(lbEntity *entity)
    {
        if (!entity)
            return;
        // 获取加粗字体
        auto boldFont = ImGui::GetIO().Fonts->Fonts[1];
        float ColumnWidth0 = ImGui::GetContentRegionAvail().x * 0.25f;

        // 绘制 lbIdentityComponent
        {
            static bool identityComponentOpen = true;
            ImGui::PushFont(boldFont);
            identityComponentOpen = ImGui::TreeNodeEx((const void *)typeid(lbIdentityComponent).hash_code(),
                                                      ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, "Identity Component");
            ImGui::PopFont();
            ImGui::Separator();

            if (identityComponentOpen)
            {
                auto &IdComp = entity->GetComponent<lbIdentityComponent>();

                // 绘制 Entity UUID
                ImGui::Columns(2, "identity_UUID_columns", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("UUID: ");
                ImGui::NextColumn();
                ImGui::Text("%llu", (unsigned long long)IdComp.m_UUID);
                ImGui::Columns(1);

                // 绘制 Entity Name，左侧名称右侧编辑框
                ImGui::Columns(2, "identity_name_columns", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("Name:");
                ImGui::NextColumn();
                char buffer[256];
                std::strcpy(buffer, IdComp.m_Name.c_str());
                if (ImGui::InputText("##entity_name_input", buffer, sizeof(buffer)))
                {
                    IdComp.m_Name = buffer;
                }
                ImGui::Columns(1);
                ImGui::TreePop();
            }
        }

        // 绘制 lbTransformComponent
        {
            static bool transformComponentOpen = true;
            ImGui::PushFont(boldFont);
            transformComponentOpen = ImGui::TreeNodeEx((const void *)typeid(lbTransformComponent).hash_code(),
                                                       ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, "Transform Component");
            ImGui::PopFont();
            ImGui::Separator();

            if (transformComponentOpen)
            {
                auto &transComp = entity->GetComponent<lbTransformComponent>();

                // 绘制 Entity Position
                ImGui::Columns(2, "transform_position_columns", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("Position: ");
                ImGui::NextColumn();
                auto position = transComp.m_Transform.GetPosition();
                if (ImGui::DragFloat3("##Position", glm::value_ptr(position), 0.1f))
                {
                    transComp.m_Transform.SetPosition(position);
                }
                ImGui::Columns(1);

                // 绘制 Entity Rotation
                ImGui::Columns(2, "transform_rotation_columns", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("Rotation: ");
                ImGui::NextColumn();
                auto rotation = transComp.m_Transform.GetRotation();
                if (ImGui::DragFloat3("##Rotation", glm::value_ptr(rotation), 0.1f))
                {
                    transComp.m_Transform.SetRotation(rotation);
                }
                ImGui::Columns(1);

                // 绘制 Entity Scale
                ImGui::Columns(2, "transform_scale_columns", false);
                ImGui::SetColumnWidth(0, ColumnWidth0);
                ImGui::Text("Scale: ");
                ImGui::NextColumn();
                auto scale = transComp.m_Transform.GetScale();
                if (ImGui::DragFloat3("##Scale", glm::value_ptr(scale), 0.1f))
                {
                    transComp.m_Transform.SetScale(scale);
                }
                ImGui::Columns(1);

                ImGui::TreePop();
            }
        }

        // 绘制 lbMeshRendererComponent
        if (entity->HasComponent<lbMeshRendererComponent>())
        {
            static bool meshRendererComponentOpen = true;
            ImGui::PushFont(boldFont);
            meshRendererComponentOpen = ImGui::TreeNodeEx((const void *)typeid(lbMeshRendererComponent).hash_code(),
                                                          ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow, "MeshRenderer Component");
            ImGui::PopFont();
            ImGui::Separator();

            if (meshRendererComponentOpen)
            {
                auto &meshRendererComp = entity->GetComponent<lbMeshRendererComponent>();
                // 几何数据
                ImGui::Text("- Geometry Properties");
                ImGui::Separator();
                // 材质
                ImGui::Text("- Material Properties");
                auto materialType = meshRendererComp.mesh->mMaterial->GetMaterialType();
                switch (materialType)
                {
                case lbMaterialType::Basic:
                    DrawBasicMaterial(std::static_pointer_cast<lbBasicMaterial>(meshRendererComp.mesh->mMaterial));
                    break;
                default:
                    break;
                }
                ImGui::TreePop();
            }
        }
    }

    void lbPropertyPanel::DrawAssetProperty()
    {
        ImGui::Text(mAssetPath.string().c_str());

        auto asset = mAssetManager->Load(mAssetPath);
        switch (asset->GetType())
        {
        case lbAssetType::Texture2D:
            DrawTexture2DAsset(std::static_pointer_cast<lbTexture2DAsset>(asset));
            break;
        default:
            break;
        }
    }

    void lbPropertyPanel::DrawTexture2DAsset(const lbTexture2DAsset::Ptr &texture)
    {
        ImGui::Text("Texture2D");
        ImGui::Image((ImTextureID)(uintptr_t)texture->GetRendererID(), ImVec2(200, 200));
    }

    void lbPropertyPanel::DrawBasicMaterial(const lbBasicMaterial::Ptr &material)
    {
        if (material)
        {
            float ColumnWidth0 = ImGui::GetContentRegionAvail().x * 0.25f;
            auto &properties = material->GetProperties();
            // baseColor
            ImGui::Columns(2, "base_color", false);
            ImGui::SetColumnWidth(0, ColumnWidth0);
            ImGui::Text("BaseColor: ");
            ImGui::NextColumn();
            ImGui::ColorEdit4("##BasicMaterial_BaseColor", glm::value_ptr(properties.baseColor));
            ImGui::Columns(1);
        }
    }

    void lbPropertyPanel::OnEntitySeleted(const lbEvent::Ptr &event)
    {
        any = event->m_UserData;
        mType = PropertyType::Entity;
    }

    void lbPropertyPanel::OnAssetSeleted(const lbEvent::Ptr &event)
    {
        any = nullptr;
        mAssetManager = static_cast<lbAssetsBrowserPanel *>(event->m_Emitter)->GetAssetManager();
        mAssetPath = std::filesystem::path(*(std::filesystem::path *)event->m_UserData);
        mType = PropertyType::Asset;
    }
} // namespace Lambix
