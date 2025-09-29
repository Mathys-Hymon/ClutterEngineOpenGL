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
    mSceneFramebuffer(frameBuffer),
    mContentBrowser(new ContentBrowser())
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
        ImGui::DockBuilderDockWindow("Scene Actors", dock_id_left);
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

    ImGui::Begin("Viewport");

    static int currentTab = 0;
    if (ImGui::BeginTabBar("ViewportTabs"))
    {
        if (ImGui::BeginTabItem("Scene"))
        {
            currentTab = 0;
            if (mOwner) mOwner->SetCamera(false);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game"))
        {
            currentTab = 1;
            if (mOwner) mOwner->SetCamera(true);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    bool hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
    if (mOwner && mOwner->mEditorCam)
        mOwner->mEditorCam->GetComponentOfType<EditorController>()->SetCanMove(hovered);

    if (mSceneFramebuffer)
    {
        ImVec2 availSize = ImGui::GetContentRegionAvail();
        float targetRatio = 16.0f / 9.0f;

        ImVec2 renderSize = availSize;
        float availRatio = (availSize.y == 0.0f) ? targetRatio : (availSize.x / availSize.y);
        if (availRatio > targetRatio)
        {
            renderSize.x = availSize.y * targetRatio;
            renderSize.y = availSize.y;
        }
        else
        {
            renderSize.x = availSize.x;
            renderSize.y = (targetRatio == 0.0f) ? availSize.y : (availSize.x / targetRatio);
        }

        ImVec2 cursorPos = ImGui::GetCursorPos();
        cursorPos.x += (availSize.x - renderSize.x) * 0.5f;
        ImGui::SetCursorPosX(cursorPos.x);

        uint32_t texID = mSceneFramebuffer->GetColorAttachment();
        ImGui::Image((void*)(intptr_t)texID, renderSize, ImVec2(0, 1), ImVec2(1, 0));

        DrawGizmoCamera();

        ImVec2 viewportStart = ImGui::GetItemRectMin();
        ImVec2 viewportEnd = ImGui::GetItemRectMax();
        (void)viewportEnd;

        ImVec2 buttonPos = ImVec2(viewportStart.x + 10, viewportStart.y + 10);
        ImGui::SetCursorScreenPos(buttonPos);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 4));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.4f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 0.8f));

        static bool is2D = false;
        bool was2D = is2D;

        ImVec4 activeColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f);
        ImVec4 activeOverColor = activeColor;
        ImVec4 activeActivationColor = activeColor;

        if (is2D)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, activeColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, activeOverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeActivationColor);
        }

        if (ImGui::Button("2D"))  is2D = !is2D;

        if (is2D && !was2D && mOwner && mOwner->mEditorCam)
        {
            mOwner->mEditorCam->GetComponentOfType<CameraComponent>()->SetProjectionMode(ProjectionMode::Orthographic);
            mOwner->mEditorCam->SetActorRotation(0);
        }
        else if (!is2D && was2D && mOwner && mOwner->mEditorCam)
        {
            mOwner->mEditorCam->GetComponentOfType<CameraComponent>()->SetProjectionMode(ProjectionMode::Perspective);
        }

        if (was2D)
            ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::Button("Move")) { /* TODO: set gizmo to translation */ }
        ImGui::SameLine();
        if (ImGui::Button("Rot")) { /* TODO: set gizmo to rotation */ }
        ImGui::SameLine();
        if (ImGui::Button("Scale")) { /* TODO: set gizmo to scaling */ }

        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);
    }
    ImGui::End();

    ImGui::Begin("Scene Actors");
    ImGui::Text("Actors list here...");
    // TODO: Populate with actual scene actor hierarchy / selection
    ImGui::End();


    ImGui::PushFont(mEditorFontTitle);
    ImGui::Begin("Inspector");
    ImGui::PopFont();

    ImGui::PushFont(mEditorFont);
    ImGui::Text("Inspector for selected actor");
    // TODO: Display properties of currently selected actor/components
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

void ImGuiLayer::DrawGizmoCamera()
{
#ifdef EDITOR
    if (!mOwner || !mOwner->mEditorCam) return;

    CameraComponent* cam = mOwner->mEditorCam->GetComponentOfType<CameraComponent>();
    if (!cam || cam != CameraComponent::GetActiveCamera()) return;

    bool is2D = cam->GetProjectionMode() == ProjectionMode::Orthographic;

    ImVec2 viewportMin = ImGui::GetWindowContentRegionMin();
    ImVec2 viewportMax = ImGui::GetWindowContentRegionMax();
    ImVec2 windowPos = ImGui::GetWindowPos();

    float gizmoSize = 80.0f;
    ImVec2 gizmoPos = ImVec2(
        windowPos.x + viewportMin.x + 5.0f,
        windowPos.y + viewportMax.y - gizmoSize - 5.0f
    );

    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    ImVec2 center(gizmoPos.x + gizmoSize * 0.5f, gizmoPos.y + gizmoSize * 0.5f);
    float arrowLength = gizmoSize * 0.4f;

    Vector3 forward = Vector3::Forward;
    Vector3 right = Vector3::Right;
    Vector3 up = Vector3::Up;

    auto ProjectAxis = [&](Vector3 axis) -> ImVec2
        {
            float x = Vector3::Dot(axis, cam->GetWorldTransform().Right());
            float y = Vector3::Dot(axis, cam->GetWorldTransform().Up());
            return ImVec2(center.x + x * arrowLength,
                center.y - y * arrowLength);
        };

    float textOffset = 0.4f;

    ImVec2 yEnd = ProjectAxis(up);
    ImVec2 xEnd = ProjectAxis(right);
    ImVec2 zEnd = ProjectAxis(forward);

    ImVec2 xEndOffset = ProjectAxis(right + right * textOffset);
    ImVec2 yEndOffset = ProjectAxis(up + up * textOffset);
    ImVec2 zEndOffset = ProjectAxis(forward + forward * textOffset);

    drawList->AddLine(center, xEnd, IM_COL32(255, 0, 0, 255), 2.0f);
    drawList->AddLine(center, yEnd, IM_COL32(0, 255, 0, 255), 2.0f);
    if (!is2D) drawList->AddLine(center, zEnd, IM_COL32(0, 0, 255, 255), 2.0f);

    float sphereRadius = 5.0f;
    drawList->AddCircleFilled(xEnd, sphereRadius, IM_COL32(255, 0, 0, 255));
    drawList->AddCircleFilled(yEnd, sphereRadius, IM_COL32(0, 255, 0, 255));
    if (!is2D) drawList->AddCircleFilled(zEnd, sphereRadius, IM_COL32(0, 0, 255, 255));

    auto DrawCenteredText = [&](ImVec2 pos, const char* text, ImU32 color) 
        {
        ImVec2 textSize = ImGui::CalcTextSize(text);
        ImVec2 textPos(pos.x - textSize.x * 0.5f, pos.y - textSize.y * 0.5f);
        drawList->AddText(textPos, color, text);
        };

    ImVec2 mousePos = ImGui::GetIO().MousePos;
    float clickRadius = 10.0f;

    auto IsHovered = [&](ImVec2 pos) -> bool
        {
            if (!is2D)
            {
                ImVec2 delta = ImVec2(mousePos.x - pos.x, mousePos.y - pos.y);
                return (delta.x * delta.x + delta.y * delta.y) <= clickRadius * clickRadius;
            }
            else return false;
        };

    ImU32 xColor = IsHovered(xEndOffset) ? IM_COL32(255, 150, 150, 255) : IM_COL32(255, 0, 0, 255);
    ImU32 yColor = IsHovered(yEndOffset) ? IM_COL32(150, 255, 150, 255) : IM_COL32(0, 255, 0, 255);
    ImU32 zColor = IsHovered(zEndOffset) ? IM_COL32(150, 150, 255, 255) : IM_COL32(0, 0, 255, 255);

    DrawCenteredText(xEndOffset, "X", xColor);
    DrawCenteredText(yEndOffset, "Y", yColor);
    if (!is2D) DrawCenteredText(zEndOffset, "Z", zColor);

    if (ImGui::IsMouseClicked(0) && !is2D)
    {
        if (IsHovered(xEndOffset))
            mOwner->mEditorCam->SetActorRotation({ 0,90,0 });
        else if (IsHovered(yEndOffset))
            mOwner->mEditorCam->SetActorRotation({90,0,0});
        else if (IsHovered(zEndOffset))
            mOwner->mEditorCam->SetActorRotation({ 0,0,0 });

        mOwner->mEditorCam->GetComponentOfType<EditorController>()->SyncRotation();
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