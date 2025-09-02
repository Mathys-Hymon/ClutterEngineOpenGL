#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class ImGuiLayer
{

public:
	ImGuiLayer();
	~ImGuiLayer();

	void BeginFrame();
	void EndFrame();
	void DrawUI();
};