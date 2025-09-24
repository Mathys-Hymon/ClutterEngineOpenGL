#include "pch.h"

#include<glad/glad.h>
#include "EditorApplication.h"
#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Input/Inputs.h>
#include "Window/Window.h"
#include <GLFW/glfw3.h>

using namespace clt;

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

#ifdef EDITOR
	FrameBufferSpecification spec;
	spec.Width = 1280;
	spec.Height = 720;
	spec.HasDepth = true;
	spec.HasColor = true;

	mViewportFramebuffer = new FrameBuffer(spec);
#endif
	mEditor = std::make_unique<clt::ImGuiLayer>(this, mViewportFramebuffer);

	if (mEngine->IsEditorMode())
	{
		clt::Inputs::Get().MapKeyToAction(EKey::F1, "enableFillMode");
		clt::Inputs::Get().MapKeyToAction(EKey::F2, "enableWireframeMode");
		clt::Inputs::Get().RegisterActionCallback("enableWireframeMode", [this] { this->ShowWireframe(); });
		clt::Inputs::Get().RegisterActionCallback("enableFillMode", [this] { this->ShowLitMode(); });
	}

#ifdef EDITOR
	Window::Get().ResizeViewport(100, 100, 1920, 1080);
#endif

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

		window.SwapBuffers();

		glfwPollEvents();
	}
}

void EditorApplication::Update()
{
	mEngine->Update();
}

void EditorApplication::Render()
{
	mEditor.get()->BeginFrame();

#ifdef EDITOR
	mViewportFramebuffer->Bind();
#endif

	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();


#ifdef EDITOR
	mViewportFramebuffer->Unbind();
#endif

	mEditor.get()->DrawUI();

	GetRenderer()->EndDraw();
	mEditor.get()->EndFrame();
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
	mEngine.reset();
	mEditor.reset();
	CLog::Shutdown();
}
