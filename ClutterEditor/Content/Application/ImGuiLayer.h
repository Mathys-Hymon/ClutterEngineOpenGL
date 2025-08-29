#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

class ImGuiLayer
{
	GLFWwindow* mWindow;

public:
	ImGuiLayer(GLFWwindow* window);
	~ImGuiLayer();

	void BeginFrame();
	void EndFrame();
	void DrawUI();
};