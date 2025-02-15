#include "pch.h"
#include<glad/glad.h>
#include <Application/Application.h>	
#include <Core/Levels/CLevel.h>
#include <GLFW/glfw3.h>

using namespace clt;

Application::Application(int pWidth, int pHeight, std::string pName, std::vector<CLevel*> pLevels) : mName(pName)
{
	mEngine = std::make_unique<CEngine>();

	if (pLevels.empty()) pLevels.push_back(new CLevel);

	mEngine->Init(pWidth, pHeight, pName, pLevels);

	CLUTTER_INFO("Application created");

	Run();
}

void Application::Run()
{
	while (!GetWindow()->ShouldClose())
	{
		Update();
		Render();

		GetWindow()->SwapBuffers();

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

Application::~Application()
{
}


void Application::Close()
{
	mEngine->Close();
}
