#include <pch.h>
#include "ImGuiLayer.h"

#ifdef EDITOR
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuizmo.h"
#include "Window/Window.h"
#include "Core/Assets/Assets.h"
#include <Application/EditorApplication.h>
#include <iostream>
#include "GraphEditor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>


ImFont* mEditorFontTitle = nullptr;
ImFont* mEditorFont = nullptr;
ImFont* mConsoleFont = nullptr;
#endif

using namespace clt;

ImGuiLayer::ImGuiLayer(EditorApplication* owner, FrameBuffer* frameBuffer)
    : mOwner(owner),

    mContentBrowser(new ContentBrowser()),
    mViewport(new EditorViewport(this, frameBuffer))
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

    mEditorFontTitle = io.Fonts->AddFontFromFileTTF("../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 18.0f);
    mEditorFont = io.Fonts->AddFontFromFileTTF("../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 15.0f);
    mConsoleFont = io.Fonts->AddFontFromFileTTF("../ClutterEngine/EngineContent/Resources/Font/JetBrains.ttf", 15.0f);

    mContentBrowser->ScanFolder("Content/");
#endif
}

void ImGuiLayer::BeginFrame()
{
#ifdef EDITOR
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
#endif
}

void ImGuiLayer::DrawUI()
{
#ifdef EDITOR

    static bool dockspaceInitialized = false;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("DockSpace_Main", nullptr, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiID dockspaceID = ImGui::GetID("DockSpace_Main");
    ImGui::DockSpace(dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    if (!dockspaceInitialized)
    {
        dockspaceInitialized = true;

        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

        ImGuiID dock_main_id = dockspaceID;
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
        ImGuiID dock_toolbar = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.07f, nullptr, &dock_main_id);
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow("ViewportToolbar", dock_toolbar);
        ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
        ImGui::DockBuilderDockWindow("Outliner", dock_id_left);
        ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
        ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
        ImGui::DockBuilderDockWindow("Console", dock_id_bottom);

        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

        ImGui::DockBuilderFinish(dockspaceID);
    }

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


    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 40), ImVec2(FLT_MAX, 40));
    ImGui::Begin("ViewportToolbar", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse);

    float windowWidth = ImGui::GetWindowWidth();
    float buttonWidth = 30.0f;
    float spacing = 10.0f;
    int   buttonCount = 4;
    float totalWidth = buttonCount * buttonWidth + (buttonCount - 1) * spacing;
    ImGui::SetCursorPosX((windowWidth - totalWidth) * 0.5f);

    GLuint offPlayID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/offPlayButton.png", "offPlayButton")
        .get()->GetID();

    GLuint onPlayID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/onPlayButton.png", "onPlayButton")
        .get()->GetID();

    GLuint offPauseID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/offPauseButton.png", "offPauseButton")
        .get()->GetID();

    GLuint onPauseID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/onPauseButton.png", "onPauseButton")
        .get()->GetID();

    GLuint quitID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/quitButton.png", "QuitButton")
        .get()->GetID();

    ImVec2 iconSize(32, 32);

    ImGui::Image((mOwner->GetMode() == EditorMode::InGame) ? (ImTextureRef)(intptr_t)onPlayID : (ImTextureRef)(intptr_t)offPlayID, iconSize);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) mOwner->SetMode(EditorMode::InGame);

    ImGui::SameLine(0, 20);

    ImGui::Image((mOwner->GetMode() == EditorMode::Paused) ? (ImTextureRef)(intptr_t)onPauseID : (ImTextureRef)(intptr_t)offPauseID, iconSize);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) mOwner->SetMode(EditorMode::Paused);

    ImGui::SameLine(0, 20);

    ImGui::Image((ImTextureRef)(intptr_t)quitID, iconSize);
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) mOwner->SetMode(EditorMode::InEditor);

    ImGui::End();

    mViewport->Draw(mFocusedActor);

    ImGui::Begin("Outliner");

    auto actors = mOwner->GetEngine().GetLevelManager()->GetCurrentLevel()->GetAllActors();

    for (auto actor : actors)
    {
        if (actor->GetName() == "EditorCamera") continue; // DEBUG TO REPLACE

        if (ImGui::Selectable(actor->GetName().c_str(), actor == mFocusedActor))
        {
            mFocusedActor = actor;
        }
    }

    ImGui::End();


    ImGui::PushFont(mEditorFontTitle);
    ImGui::Begin("Inspector");
    ImGui::PopFont();

    ImGui::PushFont(mEditorFont);

    if (mFocusedActor)
    {
        ImGui::Text(mFocusedActor->GetName().c_str());

    }

    ImGui::PopFont();
    ImGui::End();

    static bool showInfo = false;
    static bool showLog = false;
    static bool showWarning = false;
    static bool showError = false;

    const ImVec4 infoColor(0.4f, 1.0f, 0.4f, 1.0f);
    const ImVec4 logColor(1.0f, 1.0f, 1.0f, 1.0f);
    const ImVec4 warningColor(1.0f, 1.0f, 0.2f, 1.0f);
    const ImVec4 errorColor(1.0f, 0.2f, 0.2f, 1.0f);

    ImGui::PushFont(mEditorFontTitle);
    ImGui::Begin("Console");
    ImGui::PopFont();

    auto drawFilterButton = [](const char* label, bool& active, ImVec4 color)
        {
            ImVec4 baseColor = ImVec4(0.133f, 0.127f, 0.150f, 1.0f);
            if (active) baseColor = ImVec4(0.110f, 0.104f, 0.123f, 1.0f);

            ImGui::PushStyleColor(ImGuiCol_Button, baseColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(baseColor.x + 0.1f, baseColor.y + 0.1f, baseColor.z + 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, baseColor);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 6));

            bool pushedColor = false;
            if (active)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                pushedColor = true;
            }

            if (ImGui::Button(label))
                active = !active;

            if (pushedColor)
                ImGui::PopStyleColor();

            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(3);
        };

    mContentBrowser->Draw(mEditorFontTitle, mEditorFont);

    ImGui::PushFont(mEditorFont);
    drawFilterButton("INFO", showInfo, infoColor);    ImGui::SameLine();
    drawFilterButton("LOG", showLog, logColor);     ImGui::SameLine();
    drawFilterButton("WARNING", showWarning, warningColor); ImGui::SameLine();
    drawFilterButton("ERROR", showError, errorColor);
    ImGui::PopFont();

    ImGui::PushFont(mConsoleFont);
    ImGui::BeginChild("LogRegion", ImVec2(0, -30), true);

    bool noFilterActive = !showInfo && !showLog && !showWarning && !showError;

    for (const auto& entry : CLog::GetEntries())
    {
        bool show = noFilterActive;
        if (!show)
        {
            switch (entry.level)
            {
            case CLog::LogLevel::INFO:    show = showInfo;    break;
            case CLog::LogLevel::LOG:     show = showLog;     break;
            case CLog::LogLevel::WARNING: show = showWarning; break;
            case CLog::LogLevel::CERROR:  show = showError;   break;
            default:                      show = true;        break;
            }
        }

        if (show)
        {
            ImVec4 color;
            switch (entry.level)
            {
            case CLog::LogLevel::INFO:    color = infoColor;    break;
            case CLog::LogLevel::LOG:     color = logColor;     break;
            case CLog::LogLevel::WARNING: color = warningColor; break;
            case CLog::LogLevel::CERROR:  color = errorColor;   break;
            default:                      color = logColor;     break;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            std::string fullMessage = entry.timeStamp + " | " + entry.message;
            ImGui::TextWrapped("%s", fullMessage.c_str());
            ImGui::PopStyleColor();
        }
    }

    ImGui::PopFont();
    ImGui::EndChild();

    ImGui::SetCursorPosY(ImGui::GetWindowContentRegionMax().y - ImGui::GetFrameHeight());
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("Clear").x - ImGui::GetStyle().FramePadding.x * 2);

    ImGui::PushFont(mEditorFontTitle);
    if (ImGui::Button("Clear"))
        CLog::ClearEntries();
    ImGui::PopFont();

    ImGui::End();

    DrawGraphEditor();
#endif
}


void ImGuiLayer::EndFrame()
{
#ifdef EDITOR
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Render additional platform windows if multi-viewport is active
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

    // Base palette
    ImVec4 bgColor(0.157f, 0.149f, 0.176f, 1.0f);
    ImVec4 textColor(0.682f, 0.651f, 0.647f, 1.0f);

    // Window backgrounds
    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_PopupBg] = bgColor;

    // Text colors
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = ImVec4(textColor.x * 0.7f, textColor.y * 0.7f, textColor.z * 0.7f, 1.0f);

    // Headers (Tree / CollapsingHeader / Table headers)
    colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);

    //--- Buttons ---
    colors[ImGuiCol_Button] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(bgColor.x * 1.3f, bgColor.y * 1.3f, bgColor.z * 1.3f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);

    //--- Borders ---
    colors[ImGuiCol_Border] = ImVec4(bgColor.x * 0.6f, bgColor.y * 0.6f, bgColor.z * 0.6f, 1.0f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    //--- Scrollbars ---
    colors[ImGuiCol_ScrollbarBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);

    //--- Tabs ---
    colors[ImGuiCol_Tab] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
    colors[ImGuiCol_TabHovered] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_TabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);

    //--- Misc controls ---
    colors[ImGuiCol_CheckMark] = textColor;
    colors[ImGuiCol_SliderGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);

    colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
#endif
}

void clt::ImGuiLayer::DrawGraphEditor()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGui::Begin("Material Graph", nullptr, flags);
    ImGui::SetWindowFocus("Material Editor");

    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    float leftWidth = 300.0f;
    float rightWidth = windowSize.x - leftWidth;

    ImGui::BeginChild("LeftColumn", ImVec2(leftWidth, windowSize.y), true);

    ImVec2 leftSize = ImGui::GetContentRegionAvail();
    float previewHeight = leftSize.y * 0.3f; 
    float propertiesHeight = leftSize.y - previewHeight;


    ImGui::BeginChild("PreviewZone", ImVec2(leftWidth, previewHeight), true);
    //DrawPreviewMesh(); // ta fonction OpenGL/Framebuffer
    ImGui::EndChild();

    // Properties en bas
    ImGui::BeginChild("PropertiesZone", ImVec2(leftWidth, propertiesHeight), true);
    //if (selectedNode >= 0)
    //{
    //    DrawNodeProperties(selectedNode); // Inputs interactifs
    //}
    ImGui::EndChild();

    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("GraphEditor Window", ImVec2(rightWidth, windowSize.y), true);
    static GraphEditor::Options options;
    static MaterialGraphEditor graphEditor;
    static GraphEditor::ViewState viewState;
    static GraphEditor::FitOnScreen fit = GraphEditor::Fit_None;
    static bool showGraphEditor = true;

    options.mDisplayLinksAsCurves = false;
    options.mDrawIONameOnHover = false;
    options.mRounding = 10;


    options.mBackgroundColor = IM_COL32(30, 30, 30, 255);
    options.mGridColor = IM_COL32(78, 78, 78, 255);
    options.mGridBgColor = IM_COL32(40, 38, 45, 255);

    options.mLineThickness = 4;
    options.mNodeNameColor = IM_COL32(174, 166, 165, 255);
    options.mEnableMinimap = false;
    options.mBackgroundDots = true;


    GraphEditor::Show(graphEditor, options, viewState, true, &fit);
    graphEditor.HandleInputs();

    static bool temp = true;

    if (temp == true)
    {
        graphEditor.LoadGraphFromFile("Content/Resources/Materials/TestMaterial.CMaterial");
        temp = false;
    }

    if (graphEditor.mOpenContextMenu)
    {
        ImGui::OpenPopup("NodeContextMenu");
        graphEditor.mOpenContextMenu = false;
    }

    Vector2 camPos = { -viewState.mPosition.x, -viewState.mPosition.y };
    Vector2 mousePosInWindow = { ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y };

    Vector2 pos = camPos + mousePosInWindow;

    if (ImGui::BeginPopup("NodeContextMenu"))
    {
        for (auto& item : NodeTemplates)
        {
            if (item.kind == NodeKind::OutResult) continue;

            if (ImGui::MenuItem(item.name))
            {
                graphEditor.AddNode(item, pos);
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_S))
    {
        graphEditor.SaveGraphToFile("Content/Resources/Materials/TestMaterial.CMaterial");
    }

    ImGui::EndChild();

    ImGui::End();
}
