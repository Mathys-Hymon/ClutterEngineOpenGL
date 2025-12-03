#include "pch.h"
#include <Input/Inputs.h>
#include <Window/Window.h>
#include <GLFW/glfw3.h>

#include "EditorApplication.h"
#include <Editor/Services/EventBus.h>
#include <editor/Services/SelectionService.h>
#include "Editor/UI/Panels/ContentBrowserPanel.h"
#include "Editor/UI/Panels/InspectorPanel.h"
#include "Editor/UI/Panels/OutlinerPanel.h"
#include "Editor/UI/Panels/ViewportPanel.h"
#include "Editor/UI/Panels/ConsolePanel.h"
#include "Editor/UI/Panels/ViewportToolBarPanel.h"
#include "Editor/UI/Panels/ThemePanel.h"

#include <Core/Timer.h>
#include <Core/Levels/TemplateLevel/TemplateLevel.h>
#include <Core/ActorComponent/ChildActors/EditorCamera.h>
#include "Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h"

#include <Graphics/FrameBuffer/FrameBuffer.h>



using namespace clt;

EditorApplication::EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile)
{
	Init(pLevels, configFile);
}

void EditorApplication::Init(std::vector<clt::Level*> pLevels, const std::string& configFile)
{
	mEngine = std::make_unique<clt::CEngine>();
	mPanelManager = std::make_unique<editor::PanelManager>();

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
	mEditorCtx->panels = mPanelManager.get();
	mEditorCtx->app = this;
	
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

	
	mEditorCtx->themes->SetAssetIcon(AssetType::Mesh, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/meshFile.png", "mesh Icon", TextureFilter::LINEAR, false, false));
	mEditorCtx->themes->SetAssetIcon(AssetType::Font, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/fontFile.png", "font Icon", TextureFilter::LINEAR, false, false));
	mEditorCtx->themes->SetAssetIcon(AssetType::Shader, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/shaderFile.png", "shader Icon", TextureFilter::LINEAR, false, false));
	mEditorCtx->themes->SetAssetIcon(AssetType::Sound, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/audioFile.png", "audio Icon", TextureFilter::LINEAR, false, false));
	mEditorCtx->themes->SetAssetIcon(AssetType::Script, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/scriptFile.png", "script Icon", TextureFilter::LINEAR, false, false));

	mEditorCtx->themes->SetFont(editor::TextType::classic, "../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 15.0f);
	mEditorCtx->themes->SetFont(editor::TextType::title, "../ClutterEngine/EngineContent/Resources/Font/Rubik.ttf", 18.0f);
	mEditorCtx->themes->SetFont(editor::TextType::console, "../ClutterEngine/EngineContent/Resources/Font/JetBrains.ttf", 15.0f);
	
	RegisterDefaultPanels();
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

	mEditorCtx->sceneFrameBuffer->Bind();
	GetRenderer()->BeginDraw();
	GetRenderer()->Draw();
	mEditorCtx->sceneFrameBuffer->Unbind();

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

void EditorApplication::RegisterDefaultPanels()
{
	mPanelManager->RegisterPanel(
		std::make_shared<editor::ViewportPanel>(mEditorCtx.get())
	);

	mPanelManager->RegisterPanel(
		std::make_shared<editor::OutlinerPanel>(mEditorCtx.get())
	);

	mPanelManager->RegisterPanel(
		std::make_shared<editor::InspectorPanel>(mEditorCtx.get())
	);

	mPanelManager->RegisterPanel(
		std::make_shared<editor::ContentBrowserPanel>(mEditorCtx.get())
	);
	
	mPanelManager->RegisterPanel(
		std::make_shared<editor::ConsolePanel>(mEditorCtx.get())
	);
	
	mPanelManager->RegisterPanel(
		std::make_shared<editor::ViewportToolBarPanel>(mEditorCtx.get())
	);
	
	mPanelManager->RegisterPanel(
		std::make_shared<editor::ThemePanel>(mEditorCtx.get())
	);
}

EditorApplication::~EditorApplication()
{
	if (mEngine.get()) mEngine->Close();
	CLog::Shutdown();
}
