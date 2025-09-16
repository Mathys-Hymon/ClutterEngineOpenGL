#include "MainMenuMap.h"
#include "Core/All.h"
#include "UI/MainMenuHUD.h"

clt::Actor* mainMenuCam;

MainMenuMap::MainMenuMap(std::string pName)
{

}

MainMenuMap::~MainMenuMap()
{
}

void MainMenuMap::Load()
{
	mainMenuCam = AddActor<clt::Actor>("mainMenuCam");
	mainMenuCam->AddComponent<clt::CameraComponent>();

	clt::Audio::Get().SpawnSound(clt::Assets::Get().LoadAudio("Content/Resources/Audio/mainMenu.mp3", "mainMenu", AudioCategory::Music));

	mainMenuCam->AddComponent<MainMenuHUD>();
}

void MainMenuMap::Update()
{
}

void MainMenuMap::Close()
{
}
