/**
 ***************************************************************
 * @file            : lbImguiLayer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#include "Imgui/lbImguiLayer.h"
#include "Core/lbApplication.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "Utils/lbFileUtils.h"
#include "Imgui/Style/ImguiCandy/ImCandy/candy.h"

#ifdef LAMBIX_USE_OPENGL
#include "imgui_impl_opengl3.h"
#include "lbImguiLayer.h"
#endif

namespace Lambix
{
	lbImguiLayer::lbImguiLayer() : lbLayer("ImguiLayer")
	{
	}
	void lbImguiLayer::OnAttach()
	{
		// 设置 ImGui 上下文
		IMGUI_CHECKVERSION();	// 检查 ImGui 版本
		ImGui::CreateContext(); // 创建 ImGui 上下文

		// 启用一些 ImGui 的特性
		ImGuiIO &io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // 启用停靠功能
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // 启用多视口 / 平台窗口
		io.ConfigWindowsMoveFromTitleBarOnly = true;		  // 仅允许移动窗口标题栏

		// 添加字体
		io.Fonts->AddFontFromFileTTF(ASSETS("Fonts/Roboto/Roboto-Regular.ttf").string().c_str(), 17.0f);
		io.Fonts->AddFontFromFileTTF(ASSETS("Fonts/Roboto/Roboto-Bold.ttf").string().c_str(), 18.0f);
		io.Fonts->AddFontFromFileTTF(ASSETS("Fonts/Roboto/Roboto-Italic.ttf").string().c_str(), 17.0f);

		// 当启用多视口时，我们调整 WindowRounding/WindowBg，以便平台窗口看起来与常规窗口相同。
		ImGuiStyle &style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImCandy::Theme_Blender();
			// ImCandy::Theme_Nord();
		}

		// 获取 GLFW 窗口指针
		lbApplication &app = lbApplication::GetInstance();
		auto *window = static_cast<GLFWwindow *>(app.GetWindow()->GetNativeWindow());

		// 设置平台/渲染器绑定
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}
	void lbImguiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown(); // 关闭 ImGui 对 OpenGL 3 的支持
		ImGui_ImplGlfw_Shutdown();	  // 关闭 ImGui 对 GLFW 的支持
		ImGui::DestroyContext();	  // 销毁 ImGui 上下文
	}
	void lbImguiLayer::OnImGuiRender()
	{
		// ImGui::ShowDemoWindow();
	}
	void lbImguiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame(); // 开始一个新的 ImGui 帧，为 OpenGL 准备新的渲染帧
		ImGui_ImplGlfw_NewFrame();	  // 在 GLFW 中开始一个新的 ImGui 帧
		ImGui::NewFrame();			  // 告诉 ImGui 开始一个新的帧
		EnableDockSpace();
	}
	void lbImguiLayer::End()
	{
		ImGuiIO &io = ImGui::GetIO();																	  // 获取 ImGui 的输入输出对象
		lbApplication &app = lbApplication::GetInstance();												  // 获取应用程序实例
		io.DisplaySize = ImVec2((float)app.GetWindow()->GetWidth(), (float)app.GetWindow()->GetHeight()); // 设置 ImGui 的显示大小为应用程序窗口的大小

		// Rendering
		ImGui::Render();										// 渲染 ImGui 的绘制数据
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // 在 OpenGL 中渲染 ImGui 的绘制数据

		// 如果启用了多视口
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext(); // 备份当前的 OpenGL 上下文
			ImGui::UpdatePlatformWindows();								  // 更新 ImGui 的平台窗口
			ImGui::RenderPlatformWindowsDefault();						  // 在默认平台上渲染 ImGui 窗口
			glfwMakeContextCurrent(backup_current_context);				  // 将原来的 OpenGL 上下文恢复为当前上下文
		}
	}

	void lbImguiLayer::EnableDockSpace()
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
			ImGui::End();
		}
	}
} // Lambix