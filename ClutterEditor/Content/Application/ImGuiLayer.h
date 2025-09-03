#pragma once
class ImGuiLayer
{

public:
	ImGuiLayer();
	~ImGuiLayer();

	void BeginFrame();
	void EndFrame();
	void DrawUI();
};