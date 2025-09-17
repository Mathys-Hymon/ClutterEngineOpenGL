#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include"imgui.h"
#include"backends/imgui_impl_glfw.h"
#include"backends/imgui_impl_opengl3.h"

#include<glad/glad.h>
#include "EditorApplication.h"
#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Input/Inputs.h>
#include "Window/Window.h"
#include <GLFW/glfw3.h>

EditorApplication::EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile)
{
	Init(pLevels, configFile);
}

void EditorApplication::Init(std::vector<clt::Level*> pLevels, const std::string& configFile)
{
	mEngine = std::make_unique<clt::CEngine>();

	if (pLevels.empty()) pLevels.push_back(new clt::TemplateLevel());

	mEngine->Init(configFile, pLevels);
	CLUTTER_INFO("Application created");

	if (mEngine->IsEditorMode())
	{
		clt::Inputs::Get().MapKeyToAction(EKey::F1, "enableFillMode");
		clt::Inputs::Get().MapKeyToAction(EKey::F2, "enableWireframeMode");
		clt::Inputs::Get().RegisterActionCallback("enableWireframeMode", [this] { this->ShowWireframe(); });
		clt::Inputs::Get().RegisterActionCallback("enableFillMode", [this] { this->ShowLitMode(); });
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	GLFWwindow* window = clt::Window::Get().GetGLFWWindow();
		IM_ASSERT(window != nullptr);

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");

	Run();
}

void EditorApplication::Run()
{
	clt::Window& window = clt::Window::Get();

	float timer = 0;

	while (!window.ShouldClose())
	{
		clt::Timer::ComputeDeltaTime();
		Update();
		Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGui::Begin("Camera Manager");
		ImGui::Text("FOV :");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.SwapBuffers();

		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorApplication::Update()
{
	mEngine->Update();
}

void EditorApplication::Render()
{
	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();
	GetRenderer()->EndDraw();
}

void EditorApplication::ShowWireframe()
{
	mEngine->GetRenderer()->WireframeMode(true);
}

void EditorApplication::ShowLitMode()
{
	mEngine->GetRenderer()->WireframeMode(false);
}

EditorApplication::~EditorApplication()
{
	if (mEngine.get()) mEngine->Close();
	CLog::Shutdown();
}
