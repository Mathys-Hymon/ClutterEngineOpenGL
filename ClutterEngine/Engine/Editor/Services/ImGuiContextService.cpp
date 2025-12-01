#include "pch.h"
#include <imgui.h>
#include "ImGuiContextService.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "Window/Window.h"

clt::editor::ImGuiContextService::ImGuiContextService(const char* glsl_version) : mGLSL(glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(clt::Window::Get().GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

clt::editor::ImGuiContextService::~ImGuiContextService()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void clt::editor::ImGuiContextService::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void clt::editor::ImGuiContextService::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData());
    
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(clt::Window::Get().GetGLFWWindow());
    }
}

void clt::editor::ImGuiContextService::ApplyStyle(const std::function<void()>& applyTheme)
{
    if (applyTheme) applyTheme();
}
