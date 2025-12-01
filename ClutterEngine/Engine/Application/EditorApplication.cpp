#include "pch.h"
#include "EditorApplication.h"
#include <Editor/Services/EventBus.h>
#include <editor/Services/SelectionService.h>

#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Core/ActorComponent/ChildActors/EditorCamera.h>

#include <Input/Inputs.h>
#include <Window/Window.h>
#include <GLFW/glfw3.h>

#include <Graphics/FrameBuffer/FrameBuffer.h>

#include "Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h"

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

	FrameBufferSpecification spec;
	spec.Width = 1280;
	spec.Height = 720;
	spec.HasDepth = true;
	spec.HasColor = true;
	
	mEditorCtx = std::make_unique<clt::editor::EditorContext>();
	mEditorCtx->engine = &GetEngine();
	mEditorCtx->assets = &Assets::Get();
	mEditorCtx->sceneFrameBuffer = new FrameBuffer(spec);
	mEditorCtx->events = new editor::EventBus();
	mEditorCtx->selection = new editor::SelectionService();
	
	mImGuiService = std::make_unique<clt::editor::ImGuiContextService>("#version 460");
	
	mUIManager = std::make_unique<clt::editor::EditorUIManager>(mImGuiService.get(), mEditorCtx.get());
	
	SetupEditor();
	
	SetMode(EditorMode::InEditor);

	Run();
}

void EditorApplication::SetupEditor()
{
	Window& win = Window::Get();
	
	// Window Config
	win.ResizeViewportCentered(1920, 1080);
	win.RenameViewport("Clutter Editor");
	
	// Camera
	mInGameCam = CameraComponent::GetActiveCamera();
	mEditorCam = mEngine->GetLevelManager()->GetCurrentLevel()->AddActor<EditorCamera>();
	
	//KeyBinds
	Inputs::Get().MapKeyToAction(EKey::F1, "wireframe");
	Inputs::Get().MapKeyToAction(EKey::F2, "lit");

	Inputs::Get().RegisterActionCallback("wireframe", [this] { GetRenderer()->WireframeMode(true); });

	Inputs::Get().RegisterActionCallback("lit", [this] { GetRenderer()->WireframeMode(false); });
}

void EditorApplication::Run()
{
	clt::Window& win = clt::Window::Get();

	while (!win.ShouldClose())
	{
		Timer::ComputeDeltaTime();

		Update();
		Render();

		win.SwapBuffers();
		glfwPollEvents();
	}
}

void EditorApplication::Update()
{
	switch (mMode)
	{
	case EditorMode::InGame:
		mEngine->Update();
		break;
		
	case EditorMode::Paused:
	case EditorMode::InEditor:
		mEditorCam->InternalUpdate();
		mEngine->GetPhysics()->DrawDebug();
		break;
		
	default:
		break;
	}
}

void EditorApplication::Render()
{
	mUIManager->BeginFrame();

	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();

	mUIManager->Draw();

	GetRenderer()->EndDraw();
	mUIManager->EndFrame();
}

void EditorApplication::SetMode(EditorMode mode)
{
	mMode = mode;

	bool inGame = (mode == EditorMode::InGame);
	SetCamera(inGame);

	Inputs::Get().LockMouseCursor(inGame);
	Inputs::Get().SetShowMouseCursor(!inGame);
}

void EditorApplication::SetCamera(bool inGame)
{
	if(inGame && mInGameCam) mInGameCam->SetActive();
	else if(mEditorCam) mEditorCam->GetComponentOfType<CameraComponent>()->SetActive();
}

EditorApplication::~EditorApplication()
{
	if (mEngine.get()) mEngine->Close();
	CLog::Shutdown();
}
