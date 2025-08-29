#include "pch.h"
#include <Window/Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace clt;

Window& Window::Get()
{
    static Window instance;
    return instance;
}

void Window::InternalInit(u32 width, u32 height, const std::string& name, bool vsync, u32 xStart, u32 xEnd, u32 yStart, u32 yEnd)
{
    if (mIsInitialized)
        return;

    mDimensions = { static_cast<float>(width), static_cast<float>(height) };

    if (!glfwInit())
    {
        CLUTTER_ERROR("GLFW failed to init !");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mGlfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!mGlfwWindow)
    {
        CLUTTER_ERROR("Failed to create GLFW Window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(mGlfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        CLUTTER_ERROR("Failed to initialize GLAD");
        glfwTerminate();
        return;
    }

    glfwSwapInterval(vsync ? 1 : 0);
    glViewport(xStart, yStart, xEnd == -1 ? width : xEnd, yEnd == -1 ? height : yEnd);

    mIsInitialized = true;
}

Window::~Window()
{
    if (mGlfwWindow)
    {
        glfwDestroyWindow(mGlfwWindow);
        glfwTerminate();
        mGlfwWindow = nullptr;
    }
}

void Window::ResizeViewport(u32 startWidth, u32 startHeight, u32 width, u32 height)
{
    mDimensions = { static_cast<float>(width), static_cast<float>(height) };

    glfwSetWindowSize(mGlfwWindow, width, height);
    glViewport(startWidth, startHeight, width, height);
}

void Window::RenameViewport(const char* name)
{
    glfwSetWindowTitle(mGlfwWindow, name);
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
    if (mGlfwWindow)
    {
        glfwDestroyWindow(mGlfwWindow);
        glfwTerminate();
        mGlfwWindow = nullptr;
        mIsInitialized = false;
    }
}
