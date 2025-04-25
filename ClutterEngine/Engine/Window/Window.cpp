#include "pch.h"  
#include <Window/Window.h>  
#include<glad/glad.h>  
#include <GLFW/glfw3.h>  

using namespace clt;  

Window::Window(u32 pWidth, u32 pHeight,std::string pName, bool vsync)
    : mDimensions{static_cast<float>(pWidth), static_cast<float>(pHeight)}  
{  
   // Initialize GLFW  
    if (!glfwInit())
    {
        CLUTTER_ERROR("GLFW failed to init !");
    }

   // Set the GLFW Version of OpenGL  
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);  

   // Define if GLFW use the core profile  
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // Create a GLFW window  
   mGlfwWindow = glfwCreateWindow(pWidth, pHeight, pName.c_str(), nullptr, nullptr);


   // Check if the window creation failed  
   if (mGlfwWindow == nullptr) {  
       CLUTTER_ERROR("Failed to create GLFW Window");  
       glfwTerminate();  
   }  
   CLUTTER_LOG("GLFW Window Created");  

   // Make the context of the specified window current  
   glfwMakeContextCurrent(mGlfwWindow);  

   // Load all OpenGL function pointers using GLAD  
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {  
       CLUTTER_ERROR("Failed to initialise GLAD");  
       glfwTerminate();  
       return;  
   }  

   glfwSwapInterval(vsync ? 1 : 0);

   // Set the viewport size  
   glViewport(0, 0, pWidth, pHeight);  
}  

Window::~Window()  
{  
   // Destructor  
}  

void Window::ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height)  
{  
   // Resize the OpenGL viewport  
   glViewport(startWidth, startHeight, width, height);  
}

void Window::RenameViewport(const char* name)
{
    glfwSetWindowTitle(mGlfwWindow, name);
}

bool Window::ShouldClose() const  
{  
   // Check if the window should close  
   return glfwWindowShouldClose(mGlfwWindow);  
}  

void Window::SwapBuffers() const  
{  
   // Swap the front and back buffers  
   glfwSwapBuffers(mGlfwWindow);  
}  

void Window::Close()  
{  
   // Destroy the window and terminate GLFW  
   glfwDestroyWindow(mGlfwWindow);  
   glfwTerminate();  
}
