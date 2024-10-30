#include "pch.h"
#include "Window.h"
#include<glad/glad.h>
#include <GLFW/glfw3.h>


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
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, width, height);
}

GLFWwindow* Window::getRef() const
{
    return window;
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
