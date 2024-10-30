#include "pch.h"
#include<glad/glad.h>
#include "Application.h"
#include <GLFW/glfw3.h>


#include<filesystem>
namespace fs = std::filesystem;

std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
std::string contentDir = parentDir + "/FistOpenGL/Content/";


Application::Application(int width, int height, std::string name)
{
	Init(width, height, name);
	std::cout << "Application created" << std::endl;
}

void Application::Init(int width, int height, std::string name)
{
	window = new Window(width, height, name);
}


void Application::Run()
{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		 // Define the background Color
		glClear(GL_COLOR_BUFFER_BIT);				 // Clear the background color and depth
		glDepthFunc(GL_LESS);

		window->SwapBuffers();

		glfwPollEvents();
}

Application::~Application()
{
	Shutdown();
}


void Application::Shutdown()
{
	window->~Window();
	glfwTerminate();
}
