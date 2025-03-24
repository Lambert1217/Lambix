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
		{
			// 点光源
			{
				auto pointLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
				auto &ic = pointLight->GetComponent<lbIdentityComponent>();
				ic.m_Name = "pointLight1";
				auto &tc = pointLight->GetComponent<lbTransformComponent>();
				tc.m_Transform.Translate({5.0f, 5.0f, 5.0f});
				tc.m_Transform.Scale(0.3f);
				auto &lc = pointLight->AddComponent<lbLightComponent>();
				lc.Create<lbPointLight>(glm::vec2(0.001f, 10.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
			}
			{
				auto pointLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
				auto &ic = pointLight->GetComponent<lbIdentityComponent>();
				ic.m_Name = "pointLight2";
				auto &tc = pointLight->GetComponent<lbTransformComponent>();
				tc.m_Transform.Translate({-5.0f, 5.0f, 5.0f});
				tc.m_Transform.Scale(0.3f);
				auto &lc = pointLight->AddComponent<lbLightComponent>();
				lc.Create<lbPointLight>(glm::vec2(0.001f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
			}
			// 方向光
			{
				auto directionLight = m_Scene->CreateEntity("directionLight1");
				auto &lc = directionLight->AddComponent<lbLightComponent>();
				lc.Create<lbDirectionalLight>(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.3f), 0.2f);
			}
			{
				auto directionLight = m_Scene->CreateEntity("directionLight2");
				auto &lc = directionLight->AddComponent<lbLightComponent>();
				lc.Create<lbDirectionalLight>(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f);
			}
			// 聚光灯
			{
				auto spotLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
				auto &ic = spotLight->GetComponent<lbIdentityComponent>();
				ic.m_Name = "spotLight1";
				auto &tc = spotLight->GetComponent<lbTransformComponent>();
				tc.m_Transform.Translate({0.0f, 5.0f, 0.0f});
				tc.m_Transform.Scale({0.2f, 0.2f, 0.5f});
				tc.m_Transform.LookAt({-5.0f, 0.0f, -5.0f});
				auto &lc = spotLight->AddComponent<lbLightComponent>();
				lc.Create<lbSpotLight>(glm::vec2(0.001f, 50.0f), glm::vec2(0.01f, 10.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2.0f);
			}
			{
				auto spotLight = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
				auto &ic = spotLight->GetComponent<lbIdentityComponent>();
				ic.m_Name = "spotLight2";
				auto &tc = spotLight->GetComponent<lbTransformComponent>();
				tc.m_Transform.Translate({0.0f, 10.0f, 0.0f});
				tc.m_Transform.Scale({0.2f, 0.2f, 0.5f});
				tc.m_Transform.LookAt({5.0f, 0.0f, -5.0f});
				auto &lc = spotLight->AddComponent<lbLightComponent>();
				lc.Create<lbSpotLight>(glm::vec2(0.001f, 50.0f), glm::vec2(0.01f, 30.0f), glm::vec3(1.0f, 1.0f, 0.0f), 2.0f);
			}
		}
		// 创建实体
		{
			PROFILE_SCOPE("ModelLoad");
			// 平面
			auto plane = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/plane.obj")));
			auto &tc_p = plane->GetComponent<lbTransformComponent>();
			tc_p.m_Transform.Translate({0.0f, -1.5f, 0.0f});
			// 立方体
			auto cube = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/cube.obj")));
			auto &tc_c = cube->GetComponent<lbTransformComponent>();
			tc_c.m_Transform.Translate({2.0f, 0.0f, 0.0f});
			tc_c.m_Transform.Scale(2);
			// 球体
			auto sphere = m_Scene->CreateEntityFromModel(lbModelLoader::LoadFromFile(ASSETS("Meshes/sphere.obj")));
			auto &tc_s = sphere->GetComponent<lbTransformComponent>();
			tc_s.m_Transform.Translate({-2.0f, 0.0f, 0.0f});
			tc_s.m_Transform.Scale(2);
			if (sphere->HasComponent<lbMeshRendererComponent>())
			{
				auto &rc = sphere->GetComponent<lbMeshRendererComponent>();
				rc.mesh->mMaterial->SetDiffuseMap(lbTextureLoader::CreateSolidColor(0x888888ff));
			}
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
