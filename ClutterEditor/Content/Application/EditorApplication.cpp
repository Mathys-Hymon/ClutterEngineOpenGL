#include "EditorApplication.h"
#include "Window/Window.h"

EditorApplication::EditorApplication(u32 width, u32 height) : clt::Application(), mUILayer(nullptr)
{
	clt::Window::Get().InternalInit(width, height, "Clutter Editor", false);

	mUILayer = new ImGuiLayer();
}

void EditorApplication::OpenProject(const std::string& path)
{
}

void EditorApplication::Update()
{
	clt::Application::Update();
}

void EditorApplication::Render()
{
}
