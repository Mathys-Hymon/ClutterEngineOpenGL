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
	Init(pLevels, configFile);
}

void Application::Init(std::vector<Level*> pLevels, const std::string& configFile)
{
	mEngine = std::make_unique<CEngine>();

	if (pLevels.empty()) pLevels.push_back(new TemplateLevel());

	mEngine->Init(configFile, pLevels);
	CLUTTER_INFO("Application created");

	if (mEngine->isEditorMode())
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
	Window& window = Window::Get();

	while (!window.ShouldClose())
	{
		Timer::ComputeDeltaTime();
		Update();
		Render();

		window.SwapBuffers();

		glfwPollEvents();
	}
}

void Application::Update()
{
	mEngine->Update();
}

void Application::Render()
{
	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();
	GetRenderer()->EndDraw();
}

void Application::ShowWireframe()
{
	mEngine->GetRenderer()->WireframeMode(true);
}

void Application::ShowLitMode()
{
	mEngine->GetRenderer()->WireframeMode(false);
}

Application::~Application()	
{
	mEngine->Close();
	CLog::Shutdown();
}
