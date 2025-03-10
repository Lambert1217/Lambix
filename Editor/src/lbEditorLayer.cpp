#include "lbEditorLayer.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"

using namespace Lambix;

namespace Lambix
{
	lbEditorLayer::lbEditorLayer() : lbLayer("Lambix Editor")
	{
	}
	void lbEditorLayer::OnAttach()
	{
		lbFrameBufferSpecification spec;
		spec.width = lbApplication::GetInstance().GetAppSetting().WindowWidth;
		spec.height = lbApplication::GetInstance().GetAppSetting().WindowHeight;
		m_FrameBuffer = lbFrameBuffer::Create(spec);

		// temp
		m_Scene = std::make_shared<lbScene>();
		// 光源创建
		auto dLightEntity = m_Scene->CreateEntity("dLight");
		auto &dLight = dLightEntity->AddComponent<lbLightComponent>();
		dLight.Intensity = 10.f;

		// 实体创建
		auto cube = m_Scene->CreateEntity("Cube");
		auto &meshRenderer = cube->AddComponent<lbMeshRendererComponent>();
		meshRenderer.geometry = lbCubeGeometry::Create();
		meshRenderer.material = lbBasicMaterial::Create();
		meshRenderer.material->SetDiffuseMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall.jpg")));
		meshRenderer.material->SetNormalMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall_normal.jpg")));
		cube->GetComponent<lbFlagComponent>().SetRenderable(true);
	}
	void lbEditorLayer::OnDetach()
	{
	}
	void lbEditorLayer::OnUpdate(lbTimestep ts)
	{
		// 渲染到帧缓冲
		m_FrameBuffer->Bind();
		lbRendererCommand::SetClearColor({0.3f, 0.3f, 0.3f, 1.0f});
		lbRendererCommand::Clear();
		// 开始3D场景渲染
		m_Scene->OnUpdate(ts);
		m_FrameBuffer->Unbind();
	}
	void lbEditorLayer::OnEvent(Event &event)
	{
	}
	void lbEditorLayer::OnImGuiRender()
	{
		static bool dockSpaceEnabled = true;
		if (dockSpaceEnabled)
		{
			static bool dockSpaceOpen = true;
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport *viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO &io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						lbApplication::GetInstance().Quit();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		// Temp
		{
			ImGui::Begin("Scene");
			ImGui::Text("Hello Scene");
			ImGui::End();

			static bool show_log = true;
			Lambix::lbLogUI::Draw(&show_log);

			ImGui::Begin("indicator");
			ImGui::Text("indicator");
			ImGui::End();
		}

		// 实体控制面板
		{
			ImGui::Begin("Entity Control");

			// 实体控制
			for (auto &[entityHandle, entity] : m_Scene->GetEntityMap())
			{
				// 使用唯一标识符：实体ID + 名称
				std::string headerLabel = fmt::format("{}##{}", entity->GetName(), entity->GetUUID());

				if (ImGui::CollapsingHeader(headerLabel.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
				{
					auto &trans = entity->GetComponent<lbTransformComponent>();

					// 生成唯一控件ID
					const std::string entityID = std::to_string(entity->GetUUID());

					// 位置控件
					glm::vec3 pos = trans.GetLocalPosition();
					if (ImGui::DragFloat3(("Position##" + entityID).c_str(),
										  glm::value_ptr(pos), 0.1f))
					{
						trans.SetLocalPosition(pos);
					}

					// 旋转控件
					glm::quat rotation = trans.GetLocalRotation();
					glm::vec3 eulerRadians = glm::eulerAngles(rotation);
					glm::vec3 eulerDegrees = glm::degrees(eulerRadians);
					eulerDegrees = glm::vec3(
						fmod(eulerDegrees.x + 180.0f, 360.0f) - 180.0f,
						fmod(eulerDegrees.y + 180.0f, 360.0f) - 180.0f,
						fmod(eulerDegrees.z + 180.0f, 360.0f) - 180.0f);

					if (ImGui::DragFloat3(("Rotation##" + entityID).c_str(),
										  glm::value_ptr(eulerDegrees), 0.1f,
										  -FLT_MAX, FLT_MAX, "%.1f°"))
					{
						glm::vec3 newEuler = glm::radians(eulerDegrees);
						trans.SetLocalRotation(glm::quat(newEuler));
					}

					// 缩放控件
					glm::vec3 scale = trans.GetLocalScale();
					if (ImGui::DragFloat3(("Scale##" + entityID).c_str(),
										  glm::value_ptr(scale), 0.1f))
					{
						trans.SetLocalScale(scale);
					}
				}
			}

			ImGui::End();
		}

		// 视口渲染
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if (m_Scene->GetViewportWidth() != viewportPanelSize.x || m_Scene->GetViewportHeight() != viewportPanelSize.y)
			{
				m_Scene->SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
				m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			}
			static ImTextureID TextureID = (ImTextureID)(uintptr_t)m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image(TextureID, viewportPanelSize, ImVec2{0, 1}, ImVec2{1, 0});
			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}
