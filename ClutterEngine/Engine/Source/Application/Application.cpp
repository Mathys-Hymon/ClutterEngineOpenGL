#include "pch.h"
#include<glad/glad.h>
#include <Application/Application.h>	
#include <GLFW/glfw3.h>

using namespace clt;

Application::Application(int pWidth, int pHeight, std::string pName)
{
	Init(pWidth, pHeight, pName);

	CLUTTER_INFO("Application created");
}

void Application::Init(int pWidth, int pHeight, std::string pName)
{
	mWindow = new Window(pWidth, pHeight, pName);
}


void Application::Run()
{
	while (!GetWindow()->ShouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		 // Define the background Color
		glClear(GL_COLOR_BUFFER_BIT);				 // Clear the background color and depth
		glDepthFunc(GL_LESS);

		Update();
		Render();

		mWindow->SwapBuffers();

		glfwPollEvents();
	}
}

Application::~Application()
{
	Shutdown();
}


void Application::Shutdown()
{
	mWindow->Close();
	glfwTerminate();
}
