#include "pch.h"
#include<glad/glad.h>
#include <Application/Application.h>	
#include <GLFW/glfw3.h>

using namespace clt;


Application::Application(int width, int height, std::string name)
{
	Init(width, height, name);
	std::cout << "Application created" << std::endl;
}

void Application::Init(int width, int height, std::string name)
{
	mWindow = new Window(width, height, name);
}


void Application::Run()
{
	while (!GetWindow()->ShouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		 // Define the background Color
		glClear(GL_COLOR_BUFFER_BIT);				 // Clear the background color and depth
		glDepthFunc(GL_LESS);

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
	mWindow->~Window();
	glfwTerminate();
}
