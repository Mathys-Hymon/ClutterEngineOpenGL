#include "pch.h"
#include <Window/Window.h>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

using namespace clt;

Window::Window(uint32 pWidth, uint32 pHeight,std::string pName) : mName(pName), mDimensions(pWidth, pHeight)
{

    // Initialize GLFW
    glfwInit();

    // Set the GLFW Version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Define if GLFW use the core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    mGlfwWindow = glfwCreateWindow(pWidth, pHeight, pName.c_str(), NULL, NULL);

    if (mGlfwWindow == nullptr) {
        CLUTTER_ERROR("Failed to create GLFW Window");
        glfwTerminate();
    }
    CLUTTER_LOG("GLFW Window Created");
    glfwMakeContextCurrent(mGlfwWindow);

    gladLoadGL();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        CLUTTER_ERROR("Failed to initialise GLAD");
        glfwTerminate();
        return;
    }
    CLUTTER_LOG("GLAD initialised successfully");
    glViewport(0, 0, pWidth, pHeight);
}

Window::~Window()
{
}

void Window::ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height)
{
	glViewport(startWidth, startHeight, width, height);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(mGlfwWindow);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(mGlfwWindow);
}

void Window::Close()
{
    glfwDestroyWindow(mGlfwWindow);
    glfwTerminate();
}
