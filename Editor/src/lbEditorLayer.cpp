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
		m_Scene->Init();
		// 光源创建
		auto dLightEntity = m_Scene->CreateEntity("dLight");
		auto &dLight = dLightEntity->AddComponent<lbLightComponent>();
		dLight.Create<lbDirectionalLight>(glm::vec3{0.0f, -1.0f, -1.0f});

		// 实体创建
		cube1 = m_Scene->CreateEntity("Cube1");
		auto &meshRenderer1 = cube1->AddComponent<lbMeshRendererComponent>();
		meshRenderer1.geometry = lbCubeGeometry::Create();
		meshRenderer1.material = lbBasicMaterial::Create();
		meshRenderer1.material->SetDiffuseMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall.jpg")));
		meshRenderer1.material->SetNormalMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall_normal.jpg")));
		cube1->GetComponent<lbFlagComponent>().SetRenderable(true);

		auto cube2 = m_Scene->CreateEntity("Cube2");
		cube2->SetParent(cube1);
		cube2->GetComponent<lbTransformComponent>().m_Transform.Translate({2.f, 0.f, -1.f});
		auto &meshRenderer2 = cube2->AddComponent<lbMeshRendererComponent>();
		meshRenderer2.geometry = lbCubeGeometry::Create();
		meshRenderer2.material = lbBasicMaterial::Create();
		meshRenderer2.material->SetDiffuseMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall.jpg")));
		meshRenderer2.material->SetNormalMap(lbResourceManager::GetInstance().GetTexture(lbJoinPath(lbResRootDir, "Textures/brickwall_normal.jpg")));
		cube2->GetComponent<lbFlagComponent>().SetRenderable(true);
	}
	void lbEditorLayer::OnDetach()
	{
	}
	void lbEditorLayer::OnUpdate(lbTimestep ts)
	{
		// temp
		{
			auto &trans = cube1->GetComponent<lbTransformComponent>();
			trans.m_Transform.Rotate({ts * 15, ts * 10, ts * 10});
		}
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
		m_Scene->OnEvent(event);
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

		// 视口渲染
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			auto cameraSystem = static_cast<lbCameraSystem *>(m_Scene->GetSystem("CameraSystem"));
			if (cameraSystem->GetViewportWidth() != viewportPanelSize.x || cameraSystem->GetViewportHeight() != viewportPanelSize.y)
			{
				cameraSystem->SetViewportSize(viewportPanelSize.x, viewportPanelSize.y);
				m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			}
			static ImTextureID TextureID = (ImTextureID)(uintptr_t)m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image(TextureID, viewportPanelSize, ImVec2{0, 1}, ImVec2{1, 0});
			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}
