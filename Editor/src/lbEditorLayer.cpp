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
		// 根实体
		m_RootEntity = m_Scene->CreateEntity("Root");
		auto &rootTrans = m_RootEntity->GetComponent<lbTransformComponent>();
		rootTrans.SetLocalPosition({0, 0, 0});

		// 子实体1
		m_Child1Entity = m_Scene->CreateEntity("Child1");
		m_Child1Entity->SetParent(m_RootEntity);
		auto &child1Trans = m_Child1Entity->GetComponent<lbTransformComponent>();
		child1Trans.SetLocalPosition({2, 0, 0});

		// 子实体2
		m_Child2Entity = m_Scene->CreateEntity("Child2");
		m_Child2Entity->SetParent(m_Child1Entity);
		auto &child2Trans = m_Child2Entity->GetComponent<lbTransformComponent>();
		child2Trans.SetLocalPosition({0, 1, 0});
	}
	void lbEditorLayer::OnDetach()
	{
	}
	void lbEditorLayer::OnUpdate(lbTimestep ts)
	{
		// temp
		m_Scene->OnUpdate(ts);

		m_FrameBuffer->Bind();
		lbRendererCommand::SetClearColor({0.3f, 0.3f, 0.3f, 1.0f});
		lbRendererCommand::Clear();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), m_ViewportSize.x / m_ViewportSize.y, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt({0, 0, -5}, {0, 0, 0}, glm::vec3(0.0f, 1.0f, 0.0f));

		// 开始3D场景渲染
		lbRenderer3D::BeginScene(projection * view);

		// 遍历场景所有实体
		for (auto &[entityHandle, entity] : m_Scene->GetEntityMap())
		{
			if (entity->HasComponent<lbTransformComponent>())
			{
				auto &transform = entity->GetComponent<lbTransformComponent>();
				lbRenderer3D::DrawCube(transform.GetWorldMatrix(), {0.8f, 0.6f, 0.8f, 1.0f});
			}
		}

		lbRenderer3D::EndScene();
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

			// 根实体控制
			if (ImGui::CollapsingHeader("Root Entity", ImGuiTreeNodeFlags_DefaultOpen))
			{
				auto &trans = m_RootEntity->GetComponent<lbTransformComponent>();

				// 位置
				glm::vec3 pos = trans.GetLocalPosition();
				if (ImGui::DragFloat3("Position##Root", glm::value_ptr(pos), 0.1f))
				{
					trans.SetLocalPosition(pos);
				}

				// 旋转控制（改进版）
				glm::quat rotation = trans.GetLocalRotation();
				glm::vec3 eulerRadians = glm::eulerAngles(rotation); // 使用eulerAngles函数

				// 转换为角度并规范化到[-180, 180)范围
				glm::vec3 eulerDegrees = glm::degrees(eulerRadians);
				eulerDegrees = glm::vec3(
					fmod(eulerDegrees.x + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.y + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.z + 180.0f, 360.0f) - 180.0f);

				if (ImGui::DragFloat3("Rotation##Root", glm::value_ptr(eulerDegrees), 0.1f,
									  -FLT_MAX, FLT_MAX, "%.1f°"))
				{
					// 转换回弧度并创建四元数
					glm::vec3 newEuler = glm::radians(eulerDegrees);
					trans.SetLocalRotation(glm::quat(newEuler));
				}

				// 缩放
				glm::vec3 scale = trans.GetLocalScale();
				if (ImGui::DragFloat3("Scale##Root", glm::value_ptr(scale), 0.1f))
				{
					trans.SetLocalScale(scale);
				}
			}

			// 子实体1控制（新增旋转部分）
			if (ImGui::CollapsingHeader("Child1 Entity"))
			{
				auto &trans = m_Child1Entity->GetComponent<lbTransformComponent>();

				// 位置
				glm::vec3 pos = trans.GetLocalPosition();
				if (ImGui::DragFloat3("Position##Child1", glm::value_ptr(pos), 0.1f))
				{
					trans.SetLocalPosition(pos);
				}

				// 旋转控制（改进版）
				glm::quat rotation = trans.GetLocalRotation();
				glm::vec3 eulerRadians = glm::eulerAngles(rotation); // 使用eulerAngles函数

				// 转换为角度并规范化到[-180, 180)范围
				glm::vec3 eulerDegrees = glm::degrees(eulerRadians);
				eulerDegrees = glm::vec3(
					fmod(eulerDegrees.x + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.y + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.z + 180.0f, 360.0f) - 180.0f);

				if (ImGui::DragFloat3("Rotation##Child1", glm::value_ptr(eulerDegrees), 0.1f,
									  -FLT_MAX, FLT_MAX, "%.1f°"))
				{
					// 转换回弧度并创建四元数
					glm::vec3 newEuler = glm::radians(eulerDegrees);
					trans.SetLocalRotation(glm::quat(newEuler));
				}

				// 缩放
				glm::vec3 scale = trans.GetLocalScale();
				if (ImGui::DragFloat3("Scale##Child1", glm::value_ptr(scale), 0.1f))
				{
					trans.SetLocalScale(scale);
				}
			}

			// 子实体2控制（新增旋转部分）
			if (ImGui::CollapsingHeader("Child2 Entity"))
			{
				auto &trans = m_Child2Entity->GetComponent<lbTransformComponent>();

				// 位置
				glm::vec3 pos = trans.GetLocalPosition();
				if (ImGui::DragFloat3("Position##Child2", glm::value_ptr(pos), 0.1f))
				{
					trans.SetLocalPosition(pos);
				}

				// 旋转控制（改进版）
				glm::quat rotation = trans.GetLocalRotation();
				glm::vec3 eulerRadians = glm::eulerAngles(rotation); // 使用eulerAngles函数

				// 转换为角度并规范化到[-180, 180)范围
				glm::vec3 eulerDegrees = glm::degrees(eulerRadians);
				eulerDegrees = glm::vec3(
					fmod(eulerDegrees.x + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.y + 180.0f, 360.0f) - 180.0f,
					fmod(eulerDegrees.z + 180.0f, 360.0f) - 180.0f);

				if (ImGui::DragFloat3("Rotation##Child2", glm::value_ptr(eulerDegrees), 0.1f,
									  -FLT_MAX, FLT_MAX, "%.1f°"))
				{
					// 转换回弧度并创建四元数
					glm::vec3 newEuler = glm::radians(eulerDegrees);
					trans.SetLocalRotation(glm::quat(newEuler));
				}

				// 缩放
				glm::vec3 scale = trans.GetLocalScale();
				if (ImGui::DragFloat3("Scale##Child2", glm::value_ptr(scale), 0.1f))
				{
					trans.SetLocalScale(scale);
				}
			}

			ImGui::End();
		}

		// 视口渲染
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != *(glm::vec2 *)&viewportPanelSize)
			{
				m_ViewportSize = {viewportPanelSize.x, viewportPanelSize.y};
				m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			}
			static ImTextureID TextureID = (ImTextureID)(uintptr_t)m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image(TextureID, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
}
