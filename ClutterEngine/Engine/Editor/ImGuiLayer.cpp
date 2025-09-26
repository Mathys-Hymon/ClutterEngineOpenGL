

#include <pch.h>
#include "ImGuiLayer.h"

#ifdef EDITOR
#include <glad/glad.h>         
#include <GLFW/glfw3.h> 
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Window/Window.h"
#include "Core/Assets/Assets.h"
#include <Application/EditorApplication.h>
#include <iostream>
#endif

using namespace clt;

ImGuiLayer::ImGuiLayer(EditorApplication* owner, FrameBuffer* frameBuffer) : mOwner(owner), mSceneFramebuffer(frameBuffer)
{

#ifdef EDITOR

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(clt::Window::Get().GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

    SetEditorTheme();

#endif
}

void ImGuiLayer::BeginFrame()
{

#ifdef EDITOR
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
}

void ImGuiLayer::DrawUI()
{

#ifdef EDITOR

    // DockSpace
    static bool dockspaceInitialized = false;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("DockSpace_Main", nullptr, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiID dockspaceID = ImGui::GetID("DockSpace_Main");
    ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    // initial Layout
    if (!dockspaceInitialized)
    {
        dockspaceInitialized = true;
        ImGui::DockBuilderRemoveNode(dockspaceID); // clear previous layout
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

        // Split main dockspace
        ImGuiID dock_main_id = dockspaceID;
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);

        // Dock windows
        ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
        ImGui::DockBuilderDockWindow("Scene Actors", dock_id_left);
        ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
        ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
        ImGui::DockBuilderDockWindow("Console", dock_id_bottom);

        ImGui::DockBuilderFinish(dockspaceID);
    }

    // Top menu bar for camera tabs and render mode
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Open Project");
            ImGui::MenuItem("Recent projects");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Project Settings")) {}
            if (ImGui::MenuItem("Test")) {}
            ImGui::EndMenu();
        }

        std::string name = Window::Get().GetName();
        const char* projectName = name.c_str();
        float size = ImGui::CalcTextSize(projectName).x;
        float offset = 100.0f;
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - size - offset);
        ImGui::Text("%s", projectName);

        ImGui::EndMenuBar();
    }
    ImGui::End();

    //ImGui::BeginChild("ViewportToolbar", ImVec2(0, 40), false);

     //float windowWidth = ImGui::GetWindowWidth();
     //float buttonWidth = 30.0f;   
     //float spacing = 10.0f;
     //int buttonCount = 4;
     //float totalWidth = buttonCount * buttonWidth + (buttonCount - 1) * spacing;
     //ImGui::SetCursorPosX((windowWidth - totalWidth) * 0.5f);

     //GLuint playID = Assets::Get().LoadTexture("", "").get()->GetID();
     //// Boutons avec "icônes"

     //ImVec4 bg_col(0, 0, 0, 0);
     //ImVec4 tint_col(1, 1, 1, 1);
     //ImVec2 size(32, 32);
     //ImVec2 uv0(0, 0), uv1(1, 1);

     //if (ImGui::ImageButton("play_button", (ImTextureRef)(intptr_t)playID, size, uv0, uv1, bg_col, tint_col))
     //{
     //    // action quand le bouton est cliqué
     //}
     //if (ImGui::ImageButton("pause_button", (ImTextureRef)(intptr_t)playID, size, uv0, uv1, bg_col, tint_col))
     //{
     //    // action quand le bouton est cliqué
     //}

     //if (ImGui::ImageButton("quit_button", (ImTextureRef)(intptr_t)playID, size, uv0, uv1, bg_col, tint_col))
     //{
     //    // action quand le bouton est cliqué
     //}

     //if (ImGui::ImageButton("simulate_button", (ImTextureRef)(intptr_t)playID, size, uv0, uv1, bg_col, tint_col))
     //{
     //    // action quand le bouton est cliqué
     //}

     //ImGui::EndChild();
     // 
    // Viewport panel
    ImGui::Begin("Viewport");

    static int currentTab = 0;
    if (ImGui::BeginTabBar("ViewportTabs"))
    {
        if (ImGui::BeginTabItem("Scene"))
        {
            currentTab = 0;
            if (mOwner)
            {
                mOwner->SetCamera(false);
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game"))
        {
            currentTab = 1;
            if (mOwner)
            {
                mOwner->SetCamera(true);
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (mSceneFramebuffer)
    {
        ImVec2 availSize = ImGui::GetContentRegionAvail();
        float targetRatio = 16.0f / 9.0f;

        ImVec2 renderSize = availSize;
        float availRatio = availSize.x / availSize.y;
        if (availRatio > targetRatio)
        {
            renderSize.x = availSize.y * targetRatio;
            renderSize.y = availSize.y;
        }
        else
        {
            renderSize.x = availSize.x;
            renderSize.y = availSize.x / targetRatio;
        }

        // Centrage horizontal uniquement
        ImVec2 cursorPos = ImGui::GetCursorPos();
        cursorPos.x += (availSize.x - renderSize.x) * 0.5f;
        ImGui::SetCursorPosX(cursorPos.x);

        // Image
        uint32_t texID = mSceneFramebuffer->GetColorAttachment();
        ImGui::Image((void*)(intptr_t)texID, renderSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();

    // Scene Actors
    ImGui::Begin("Scene Actors");
    ImGui::Text("Actors list here...");
    ImGui::End();

    // Inspector
    ImGui::Begin("Inspector");
    ImGui::Text("Inspector for selected actor");
    ImGui::End();

    // Content Browser
    ImGui::Begin("Content Browser");
    ImGui::Text("Content hierarchy here");
    ImGui::End();

    // Console
    ImGui::Begin("Console");

    for (const auto& entry : CLog::GetEntries())
    {
        ImVec4 color;

        switch (entry.level)
        {
        case CLog::LogLevel::INFO:    color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f); break;
        case CLog::LogLevel::WARNING: color = ImVec4(1.0f, 1.0f, 0.2f, 1.0f); break;
        case CLog::LogLevel::CERROR:  color = ImVec4(1.0f, 0.2f, 0.2f, 1.0f); break;
        default:                      color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); break;
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextWrapped("%s", entry.message.c_str());
        ImGui::PopStyleColor();
    }

    if (ImGui::Button("Clear")) CLog::ClearEntries();

    //ImGui::End();
    ImGui::End();

#endif
}

void ImGuiLayer::EndFrame()
{

#ifdef EDITOR
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

#endif
}

ImGuiLayer::~ImGuiLayer()
{

#ifdef EDITOR
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
}

void ImGuiLayer::SetEditorTheme()
{
#ifdef EDITOR
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Couleurs de base
    ImVec4 bgColor(0.157f, 0.149f, 0.176f, 1.0f);    // 28262D
    ImVec4 textColor(0.682f, 0.651f, 0.647f, 1.0f);  // AEA6A5

    // Fond général
    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_PopupBg] = bgColor;

    // Textes
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = ImVec4(textColor.x * 0.7f, textColor.y * 0.7f, textColor.z * 0.7f, 1.0f);

    // Headers
    colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);

    // Boutons
    colors[ImGuiCol_Button] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(bgColor.x * 1.3f, bgColor.y * 1.3f, bgColor.z * 1.3f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);

    // Bordures et séparateurs
    colors[ImGuiCol_Border] = ImVec4(bgColor.x * 0.6f, bgColor.y * 0.6f, bgColor.z * 0.6f, 1.0f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);

    // Checkbox / Slider / Selectables
    colors[ImGuiCol_CheckMark] = textColor;
    colors[ImGuiCol_SliderGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
#endif // EDITOR

}
