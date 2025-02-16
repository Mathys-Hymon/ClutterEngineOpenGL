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

   // Create a GLFW window  
   mGlfwWindow = glfwCreateWindow(pWidth, pHeight, pName.c_str(), NULL, NULL);  

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
