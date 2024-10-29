#include "pch.h"

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"


#include<filesystem>
namespace fs = std::filesystem;


std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
std::string contentDir = parentDir + "/FistOpenGL/Content/";

const unsigned int width = 800;
const unsigned int height = 800;

Application::Application()
{
	Init();
	std::cout << "Application created" << std::endl;
}

void Application::Init()
{
	window = new Window(width, height, "Clutter Engine");
}


void Application::Run()
{
	while (!window->ShouldClose()) {

		// Rendu
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Couleur de fond
		glClear(GL_COLOR_BUFFER_BIT); // Effacer le tampon de couleur

		// Échanger les buffers
		window->SwapBuffers();

		glfwPollEvents();
	}
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
