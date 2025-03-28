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
			// AddPointLight(m_Scene, "pointLight1", {5.0f, 5.0f, 5.0f}, {1.0f, 0.0f, 0.0f});
			AddPointLight(m_Scene, "pointLight2", {-3.0f, 3.0f, 3.0f}, {1.0f, 1.0f, 1.0f}, {0.001f, 10.f}, 1.4f);
			//  AddDirectionLight(m_Scene, "directionLight1", {-1.0f, -4.0f, 2.0f}, {1.0f, 1.0f, 1.0f}, 0.01);
			//  AddSpotLight(m_Scene, "spotLight1", {0.0f, 10.0f, 0.0f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f}, 5, {0.001f, 50.f});
		}
		// 创建实体
		{
			// 平面
			auto plane = m_Scene->CreateEntityFromModel(lbCache::Get()->GetModel(ASSETS("Meshes/plane.obj")));
			auto &tc_p = plane->GetComponent<lbTransformComponent>();
			tc_p.m_Transform.Translate({0.0f, -1.5f, 0.0f});
			if (plane->HasComponent<lbMeshRendererComponent>())
			{
				auto &rc = plane->GetComponent<lbMeshRendererComponent>();
				rc.mesh->mMaterial = lbPhongMaterial::Create();
			}
			// 立方体
			auto cube = m_Scene->CreateEntityFromModel(lbCache::Get()->GetModel(ASSETS("Meshes/cube.obj")));
			auto &tc_c = cube->GetComponent<lbTransformComponent>();
			tc_c.m_Transform.Translate({2.0f, 0.0f, 0.0f});
			tc_c.m_Transform.Scale(2);
			if (cube->HasComponent<lbMeshRendererComponent>())
			{
				auto &rc = cube->GetComponent<lbMeshRendererComponent>();
				rc.mesh->mMaterial = lbPhongMaterial::Create();
			}
			// 球体
			auto sphere = m_Scene->CreateEntityFromModel(lbCache::Get()->GetModel(ASSETS("Meshes/sphere.obj")));
			auto &tc_s = sphere->GetComponent<lbTransformComponent>();
			tc_s.m_Transform.Translate({-2.0f, 0.0f, 0.0f});
			tc_s.m_Transform.Scale(2);
			if (sphere->HasComponent<lbMeshRendererComponent>())
			{
				auto &rc = sphere->GetComponent<lbMeshRendererComponent>();
				rc.mesh->mMaterial = lbPhongMaterial::Create();
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

	void lbEditorLayer::AddPointLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &posiiton, const glm::vec3 &color, const glm::vec2 &range, float intensity)
	{
		auto pointLight = scene->CreateEntityFromModel(lbCache::Get()->GetModel(ASSETS("Meshes/sphere.obj")));
		auto &ic = pointLight->GetComponent<lbIdentityComponent>();
		ic.m_Name = name;
		auto &tc = pointLight->GetComponent<lbTransformComponent>();
		tc.m_Transform.Translate(posiiton);
		tc.m_Transform.Scale(0.3f);
		auto &lc = pointLight->AddComponent<lbLightComponent>();
		lc.Create<lbPointLight>(range, color, intensity);
	}

	void lbEditorLayer::AddDirectionLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &direction, const glm::vec3 &color, float intensity)
	{
		auto directionLight = scene->CreateEntity(name);
		auto &lc = directionLight->AddComponent<lbLightComponent>();
		lc.Create<lbDirectionalLight>(direction, color, intensity);
	}

	void lbEditorLayer::AddSpotLight(const std::shared_ptr<lbScene> &scene, const std::string &name, const glm::vec3 &posiiton, const glm::vec3 &lookAt, const glm::vec3 &color, float intensity, const glm::vec2 &range, const glm::vec2 &angle)
	{
		auto spotLight = scene->CreateEntityFromModel(lbCache::Get()->GetModel(ASSETS("Meshes/cube.obj")));
		auto &ic = spotLight->GetComponent<lbIdentityComponent>();
		ic.m_Name = name;
		auto &tc = spotLight->GetComponent<lbTransformComponent>();
		tc.m_Transform.Translate(posiiton);
		tc.m_Transform.Scale({0.2f, 0.2f, 0.5f});
		tc.m_Transform.LookAt(lookAt);
		auto &lc = spotLight->AddComponent<lbLightComponent>();
		lc.Create<lbSpotLight>(range, angle, color, intensity);
	}
}
