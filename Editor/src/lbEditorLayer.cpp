#include "lbEditorLayer.h"
#include "imgui.h"
#include "Panels/lbSceneHierarchyPanel.h"
#include "Panels/lbPropertyPanel.h"
#include "Panels/lbProfilePanel.h"
#include "Panels/lbViewportPanel.h"
#include "Panels/lbLogPanel.h"
#include "Panels/lbMenuBarPanel.h"
#include "Panels/lbAssetsBrowserPanel.h"

using namespace Lambix;

namespace Lambix
{
	lbEditorLayer::lbEditorLayer() : lbLayer("Lambix Editor")
	{
		lbEventDispatcher::Get()->addEventListener<lbEditorLayer>("OpenProject", this, &lbEditorLayer::OnOpenProject);
	}
	lbEditorLayer::~lbEditorLayer()
	{
		lbEventDispatcher::Get()->removeEventListener<lbEditorLayer>("OpenProject", this, &lbEditorLayer::OnOpenProject);
	}
	void lbEditorLayer::OnAttach()
	{
		PROFILE_SCOPE("lbEditorLayer::OnAttach");
		// Panels
		m_Panels.emplace("lbMenuBarPanel", lbMenuBarPanel::Create());
		m_Panels.emplace("lbPropertyPanel", lbPropertyPanel::Create());
		m_Panels.emplace("lbSceneHierarchyPanel", lbSceneHierarchyPanel::Create());
		m_Panels.emplace("lbProfilePanel", lbProfilePanel::Create());
		m_Panels.emplace("lbViewportPanel", lbViewportPanel::Create());
		m_Panels.emplace("lbLogPanel", lbLogPanel::Create(lbLog::GetImGuiSink()));
		m_Panels.emplace("lbAssetsBrowserPanel", lbAssetsBrowserPanel::Create());
	}
	void lbEditorLayer::OnDetach()
	{
	}
	void lbEditorLayer::OnUpdate(lbTimestep ts)
	{
		PROFILE_SCOPE("lbEditorLayer::OnUpdate");
		// 开始3D场景渲染
		if (mCurrentProject)
		{
			lbScene::Ptr scene = mCurrentProject->GetActiveScene();
			if (scene)
				scene->OnUpdate(ts);
		}
	}
	void lbEditorLayer::OnImGuiRender()
	{
		PROFILE_SCOPE("lbEditorLayer::OnImGuiRender");
		// UI渲染
		for (auto it : m_Panels)
		{
			it.second->OnImGuiRender();
		}

		// TODO: temp 测试资产管理器
		// ImGui::Begin("Assets Test");
		// if (ImGui::Button("Des dog.ltex"))
		// {
		// 	auto it = std::static_pointer_cast<lbTexture2DAsset>(m_AssetManager->Load("Textures\\dog.ltex"));
		// 	LOG_INFO("dog.ltex");
		// }
		// ImGui::End();
	}

	void lbEditorLayer::OnOpenProject(const lbEvent::Ptr &event)
	{
		mCurrentProject = static_cast<lbProject *>(event->m_UserData);
		auto scene = mCurrentProject->GetActiveScene();
		// 设置ui
		std::static_pointer_cast<lbSceneHierarchyPanel>(m_Panels["lbSceneHierarchyPanel"])->SetContext(scene);
		std::static_pointer_cast<lbProfilePanel>(m_Panels["lbProfilePanel"])->SetContext(static_cast<lbRendererSystem *>(scene->GetSystem("RendererSystem")));
		std::static_pointer_cast<lbViewportPanel>(m_Panels["lbViewportPanel"])->SetContext(scene);
		std::static_pointer_cast<lbAssetsBrowserPanel>(m_Panels["lbAssetsBrowserPanel"])->SetContext(mCurrentProject->GetAssetManager());
	}
}
