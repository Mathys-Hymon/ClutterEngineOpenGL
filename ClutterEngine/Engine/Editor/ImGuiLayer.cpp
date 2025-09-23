

#include <pch.h>
#include "ImGuiLayer.h"

#ifdef EDITOR
#include <glad/glad.h>            // glad EN PREMIER
#include <GLFW/glfw3.h>           // ensuite glfw
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Window/Window.h"
#include <iostream>
#endif

using namespace clt;

ImGuiLayer::ImGuiLayer()
{

#ifdef EDITOR
	// Set up ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(clt::Window::Get().GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#endif
}

void ImGuiLayer::BeginFrame()
{

#ifdef EDITOR
	glClearColor(0.045f, 0.054f, 0.087f, 1.0f);				    // Define the background Color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		    // Clear the background color and depth
	glDepthFunc(GL_LESS);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
}

void ImGuiLayer::DrawUI()
{

#ifdef EDITOR

	if (mSceneFramebuffer)
	{
		ImGui::Begin("Viewport");
		ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::Image((void*)(intptr_t)mSceneFramebuffer->GetColorAttachment(),
			size,
			ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}

#endif
}

void ImGuiLayer::EndFrame()
{

#ifdef EDITOR
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
