#include "lbEditorLayer.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "Panels/lbSceneHierarchyPanel.h"
#include "Panels/lbPropertyPanel.h"
#include "Panels/lbProfilePanel.h"
#include "Panels/lbViewportPanel.h"
#include "Panels/lbLogPanel.h"
#include "Panels/lbMenuBarPanel.h"

using namespace Lambix;

namespace Lambix
{
	lbEditorLayer::lbEditorLayer() : lbLayer("Lambix Editor")
	{
	}
	void lbEditorLayer::OnAttach()
	{
		PROFILE_SCOPE("lbEditorLayer::OnAttach");
		// temp
		m_Scene = std::make_shared<lbScene>();
		// 光源创建
		auto dLightEntity = m_Scene->CreateEntity("dLight");
		auto &dLight = dLightEntity->AddComponent<lbLightComponent>();
		dLight.Create<lbDirectionalLight>(glm::vec3{0.0f, -1.0f, -1.0f});
		// 创建实体
		{
			PROFILE_SCOPE("ModelLoad");
			m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/plane.obj")));
			m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/cube.obj")));
			m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
			// m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Models/tian/tian.fbx")));
		}

		// Panels
		m_Panels.push_back(lbMenuBarPanel::Create());
		m_Panels.push_back(lbSceneHierarchyPanel::Create(m_Scene));
		m_Panels.push_back(lbPropertyPanel::Create());
		m_Panels.push_back(lbProfilePanel::Create(dynamic_cast<lbRendererSystem *>(m_Scene->GetSystem("RendererSystem"))));
		m_Panels.push_back(lbViewportPanel::Create(m_Scene));
		m_Panels.push_back(lbLogPanel::Create(lbLog::GetImGuiSink()));
	}
	void lbEditorLayer::OnDetach()
	{
	}
	void lbEditorLayer::OnUpdate(lbTimestep ts)
	{
		PROFILE_SCOPE("lbEditorLayer::OnUpdate");
		// 开始3D场景渲染
		m_Scene->OnUpdate(ts);
	}
	void lbEditorLayer::OnImGuiRender()
	{
		PROFILE_SCOPE("lbEditorLayer::OnImGuiRender");
		// UI渲染
		for (auto panel : m_Panels)
		{
			panel->OnImGuiRender();
		}
	}
}
