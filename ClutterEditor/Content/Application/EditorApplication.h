#pragma once
#include <Application/Application.h>
#include "ImGuiLayer.h"

	class clt::Window;
	class EditorApplication : public clt::Application 
	{
		ImGuiLayer* mUILayer;
		bool mProjectOpened;

		virtual void Update() override;
		virtual void Render() override;

	public:

		EditorApplication(u32 width, u32 height);
		~EditorApplication() = default;

		void OpenProject(const std::string& path);
	};