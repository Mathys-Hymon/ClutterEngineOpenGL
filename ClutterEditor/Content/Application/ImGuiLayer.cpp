#include "ImGuiLayer.h"
#include "Window/Window.h"

ImGuiLayer::ImGuiLayer()
{
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
    ImGui::Separator();

    // --- Bouton Browse (placeholder pour vrai file dialog) ---
    if (ImGui::Button("Browse..."))
    {
        std::string fakePath = "C:/Users/Mathys/Projects/NewProject";
        editorApp->OpenProject(fakePath);
    }

    ImGui::Spacing();
    ImGui::Text("Recent Projects:");
    ImGui::Separator();

    for (auto& project : sRecentProjects)
    {
        if (ImGui::Selectable(project.c_str()))
        {
            editorApp->OpenProject(project);
        }
    }

    ImGui::End();
}

void ImGuiLayer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}