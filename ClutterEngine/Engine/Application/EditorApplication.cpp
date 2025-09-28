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
	spec.Width = 1920;
	spec.Height = 1080;
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

	Window::Get().ResizeViewportCentered(1920, 1080);

	mInGameCam = CameraComponent::GetActiveCamera();
	mEditorCam = mEngine->GetLevelManager()->GetCurrentLevel()->AddActor<EditorCamera>();

	SetMode(clt::EditorMode::InEditor);

	Texture* tex = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Icon/clutterLogoLight.png", "EditorLogo").get();
	unsigned char* pixels = tex->GetPixels();

	GLFWimage image;
	image.width = static_cast<int>(tex->GetWidth());
	image.height = static_cast<int>(tex->GetHeight());
	image.pixels = pixels;

	glfwSetWindowIcon(Window::Get().GetGLFWWindow(), 1, &image);

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
		mEditorCam->InternalUpdate();
		mEngine->GetPhysics()->DrawDebug();
		break;
	case EditorMode::InEditor:
		mEditorCam->InternalUpdate();
		mEngine->GetPhysics()->DrawDebug();
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
		SetCamera(true);
		Inputs::Get().LockMouseCursor(true);
		Inputs::Get().SetShowMouseCursor(false);
		break;

	case clt::EditorMode::Paused:
		SetCamera(false);
		Inputs::Get().LockMouseCursor(false);
		Inputs::Get().SetShowMouseCursor(true);
		break;

	case clt::EditorMode::InEditor:
		SetCamera(false);
		Inputs::Get().LockMouseCursor(false);
		Inputs::Get().SetShowMouseCursor(true);
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
