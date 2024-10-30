#include "Application.h"
#include <string>
#include <iostream>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

int main()
{
    std::cout << "Clutter Editor" << std::endl;
	Application app(800, 800,"Editor Window"); // Create an instance of the application
    
    // Set up ImGUI
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui::StyleColorsDark();
    //ImGui_ImplGlfw_InitForOpenGL(app.GetWindow(), true);
    //ImGui_ImplOpenGL3_Init("#version 330");


    while (!app.GetWindow()->ShouldClose())
    {
        app.Run();
    }
     // Run the application loop for the editor
    return 0;
    
}
