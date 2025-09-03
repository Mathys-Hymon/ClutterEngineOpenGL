#include "EditorApplication.h"
#include "Window/Window.h"

int temp = 0;

EditorApplication::EditorApplication(u32 width, u32 height) : clt::Application(), mProjectOpened(false)
{
	Update();
}

void EditorApplication::OpenProject(const std::string& path)
{
}

void EditorApplication::Update()
{

	clt::Window& window = clt::Window::Get();
	
	mUILayer = new ImGuiLayer();
	clt::Application::Init({});

	while (!window.ShouldClose())
	{
		clt::Timer::ComputeDeltaTime();
		clt::Application::Update();
		clt::Application::Render();
		Render();
		window.SwapBuffers();
	}
}

void EditorApplication::Render()
{
}
