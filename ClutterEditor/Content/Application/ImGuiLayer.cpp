#include "ImGuiLayer.h"

#ifndef ImGuiConfigFlags_DockingEnable
#define ImGuiConfigFlags_DockingEnable (1 << 6)
#endif

#ifndef ImGuiConfigFlags_ViewportsEnable
#define ImGuiConfigFlags_ViewportsEnable (1 << 10)
#endif

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
}

void ImGuiLayer::EndFrame()
{
}

void ImGuiLayer::DrawUI()
{
}
