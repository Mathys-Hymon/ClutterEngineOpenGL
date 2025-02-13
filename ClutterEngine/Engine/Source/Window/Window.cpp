#include "pch.h"
#include <Window/Window.h>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

using namespace clt;
GLFWwindow* window;

Window::Window(unsigned int width, unsigned int height, const std::string& title)
{

    // Initialize GLFW
    glfwInit();

    // Set the GLFW Version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Define if GLFW use the core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == nullptr) {
        CLUTTER_ERROR("Failed to create GLFW Window");
        glfwTerminate();
    }
    CLUTTER_LOG("GLFW Window Created");
    glfwMakeContextCurrent(window);

    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        CLUTTER_ERROR("Failed to initialise GLAD");
        glfwTerminate();
        return;
    }
    CLUTTER_LOG("GLAD initialised successfully");
    glViewport(0, 0, width, height);
}

void Window::ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height)
{
	glViewport(startWidth, startHeight, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(window);
}
