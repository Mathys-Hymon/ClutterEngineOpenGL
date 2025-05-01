#include "pch.h"
#include<glad/glad.h>
#include <Application/Application.h>	
#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Input/Input.h>
#include <GLFW/glfw3.h>

using namespace clt;

Application::Application(std::vector<Level*> pLevels, const std::string& configFile)
{
	if (pLevels.empty()) pLevels.push_back(new TemplateLevel());

	CEngine::Get().Init(configFile, pLevels);
	CLUTTER_INFO("Application created");

	if (CEngine::Get().isEditorMode())
	{
		Input::Get().MapKeyToAction(EKey::F1, "enableFillMode");
		Input::Get().MapKeyToAction(EKey::F2, "enableWireframeMode");
		Input::Get().RegisterActionCallback("enableWireframeMode", [this] { this->ShowWireframe(); });
		Input::Get().RegisterActionCallback("enableFillMode", [this] { this->ShowLitMode(); });
	}

	Run();
}

void Application::Run()
{
	while (!CEngine::Get().GetWindow()->ShouldClose())
	{
		Timer::ComputeDeltaTime();
		Update();
		Render();

		CEngine::Get().GetWindow()->SwapBuffers();

		glfwPollEvents();
	}
}

void Application::Update()
{
	CEngine::Get().Update();
}

void Application::Render()
{
	CEngine::Get().GetRenderer()->BeginDraw();
	CEngine::Get().GetRenderer()->Draw();
	CEngine::Get().GetRenderer()->EndDraw();
}

void Application::ShowWireframe()
{
	CEngine::Get().GetRenderer()->WireframeMode(true);
}

void Application::ShowLitMode()
{
	CEngine::Get().GetRenderer()->WireframeMode(false);
}

Application::~Application()	
{
	CEngine::Get().Close();
	CLog::Shutdown();
}
