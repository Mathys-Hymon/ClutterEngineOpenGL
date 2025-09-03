
#include <glad/glad.h>            // glad EN PREMIER
#include <GLFW/glfw3.h>           // ensuite glfw
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuiLayer.h"
#include "Window/Window.h"
#include <iostream>

GLFWwindow* window;

ImGuiLayer::ImGuiLayer()
{
	// Initialize GLFW
	glfwInit();


	// Set the GLFW Version of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Define if GLFW use the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Create the window
	window = glfwCreateWindow(300, 500, "first OpenGL", NULL, NULL);

	if (window == NULL)												// Return error if window dont create correctly
	{
		std::cout << "\n\nFailed to create GLFW Window\n\n" << std::endl;

		glfwTerminate();
	}

	// Set the window to the current context
	glfwMakeContextCurrent(window);

	// Load Glad for OpenGL
	gladLoadGL();

	// Set the viewport Size
	glViewport(0, 0, 300, 500);

	glEnable(GL_DEPTH_TEST);


	clt::Window::Get().SetGLFWWindow(window);

	// Set up ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::BeginFrame()
{
	//glClearColor(0.045f, 0.054f, 0.087f, 1.0f);				    // Define the background Color
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		    // Clear the background color and depth
	//glDepthFunc(GL_LESS);

	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
}

void ImGuiLayer::DrawUI()
{
	glClearColor(0.045f, 0.054f, 0.087f, 1.0f);				    // Define the background Color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		    // Clear the background color and depth
	glDepthFunc(GL_LESS);


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	static float f = 0.0f;
	static int counter = 0;

	bool test = false;
	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &test);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &test);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Swap the back buffer with the front
	glfwSwapBuffers(window);
	// Manage all GLFW events
	glfwPollEvents();
}

void ImGuiLayer::EndFrame()
{

    //ImGui::End();
    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}