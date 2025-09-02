#include "ImGuiLayer.h"
#include "Window/Window.h"

ImGuiLayer::ImGuiLayer()
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(clt::Window::Get().GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();
}

void ImGuiLayer::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::DrawUI()
{
    ImGui::Begin("Clutter Editor - Project Launcher");

    ImGui::Text("Open Project");
}

void ImGuiLayer::EndFrame()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiLayer::~ImGuiLayer()
{
}