#pragma once
#include <Core/CEngine.h>
#include <Application/Application.h>
#include "ImGuiLayer.h"

namespace clt
{
	class CLUTTER_API EditorApplication : public Application 
	{
		ImGuiLayer* mUILayer;

		virtual void Update() override;
		virtual void Render() override;

	public:

		EditorApplication();
		~EditorApplication() = default;

		void OpenProject(const std::string& path);
	};
}