#include "pch.h"
#include<glad/glad.h>
#include <Application/Application.h>	
#include <GLFW/glfw3.h>

using namespace clt;

Application::Application(int pWidth, int pHeight, std::string pName) : mName(pName)
{
	Init(pWidth, pHeight, pName);

	CLUTTER_INFO("Application created");

	Run();
}

void Application::Init(int pWidth, int pHeight, std::string pName)
{
	mEngine = std::make_unique<CEngine>();
	mEngine->Init(pWidth, pHeight, pName);
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
