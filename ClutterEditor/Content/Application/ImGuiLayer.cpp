#include "ImGuiLayer.h"

ImGuiLayer::ImGuiLayer(GLFWwindow* window) : mWindow(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Multi-viewport

    ImGui::StyleColorsDark(); // Dark theme

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init("#version 150"); // adapte au GLSL utilisé
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::DrawUI()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

    // Panels
    ImGui::Begin("Content Browser");
    ImGui::Text("Assets list goes here");
    ImGui::End();

    ImGui::Begin("Properties");
    ImGui::Text("Actor properties go here");
    ImGui::End();

    ImGui::Begin("Viewport");
    mViewportSize = ImGui::GetContentRegionAvail();
    mViewportPos = ImGui::GetCursorScreenPos();
    // Ici tu pourras dessiner ton framebuffer OpenGL
    ImGui::End();

    ImGui::End(); // DockSpace window
}
