#include "pch.h"

#include<glad/glad.h>
#include "EditorApplication.h"
#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Core/ActorComponent/ChildActors/EditorCamera.h>
#include <Physics/IPhysics.h>
#include <Input/Inputs.h>
#include "Window/Window.h"
#include <GLFW/glfw3.h>

using namespace clt;

EditorApplication::EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile) : mInGameCam(nullptr), mEditorCam(nullptr)
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


#ifdef EDITOR

	clt::Inputs::Get().MapKeyToAction(EKey::F1, "enableFillMode");
	clt::Inputs::Get().MapKeyToAction(EKey::F2, "enableWireframeMode");
	clt::Inputs::Get().RegisterActionCallback("enableWireframeMode", [this] { this->ShowWireframe(); });
	clt::Inputs::Get().RegisterActionCallback("enableFillMode", [this] { this->ShowLitMode(); });

	Window::Get().ResizeViewport(100, 100, 1920, 1080);

	mEngine->Update();

	mInGameCam = CameraComponent::GetActiveCamera();
	mEditorCam = mEngine->GetLevelManager()->GetCurrentLevel()->AddActor<EditorCamera>();

	SetMode(clt::EditorMode::InEditor);

#endif


	Run();
}

void EditorApplication::Run()
{
	clt::Window& window = clt::Window::Get();

	while (!window.ShouldClose())
	{
		Timer::ComputeDeltaTime();

		Update();
		Render();

		window.SwapBuffers();

		glfwPollEvents();
	}
}

void EditorApplication::Update()
{
#ifdef EDITOR

	switch (mMode)
	{
	case EditorMode::InGame:
		mEngine->Update();

		break;
	case EditorMode::Paused:
		Inputs::Get().Update();
		mEditorCam->InternalUpdate();
		break;
	case EditorMode::InEditor:
		Inputs::Get().Update();
		mEditorCam->InternalUpdate();
		break;
	default:
		break;
	}
#else
	mEngine->Update();
#endif
}

void EditorApplication::Render()
{
	mEditor->BeginFrame();

#ifdef EDITOR
	mViewportFramebuffer->Bind();
#endif

	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();


#ifdef EDITOR
	mViewportFramebuffer->Unbind();
#endif

	mEditor->DrawUI();

	GetRenderer()->EndDraw();
	mEditor->EndFrame();
}

void EditorApplication::ShowWireframe()
{
	mEngine->GetRenderer()->WireframeMode(true);
}

void EditorApplication::ShowLitMode()
{
	mEngine->GetRenderer()->WireframeMode(false);
}

void EditorApplication::SetMode(EditorMode mode)
{
	mMode = mode;

	switch (mode)
	{
	case clt::EditorMode::InGame:
		Inputs::Get().LockMouseCursor(true);
		Inputs::Get().SetShowMouseCursor(false);
		if (mInGameCam) mInGameCam->SetActive();
		break;

	case clt::EditorMode::Paused:
		Inputs::Get().LockMouseCursor(false);
		Inputs::Get().SetShowMouseCursor(true);
		if (mEditorCam) mEditorCam->GetComponentOfType<CameraComponent>()->SetActive();
		break;

	case clt::EditorMode::InEditor:
		Inputs::Get().LockMouseCursor(false);
		Inputs::Get().SetShowMouseCursor(true);
		if (mEditorCam) mEditorCam->GetComponentOfType<CameraComponent>()->SetActive();
		break;
	default:
		break;
	}
}

void EditorApplication::SetCamera(bool inGame)
{
	if(inGame && mInGameCam) mInGameCam->SetActive();
	else if(mEditorCam) mEditorCam->GetComponentOfType<CameraComponent>()->SetActive();
}

EditorApplication::~EditorApplication()
{
	if (mEngine.get()) mEngine->Close();
	mEngine.reset();
	mEditor.reset();
	CLog::Shutdown();
}
