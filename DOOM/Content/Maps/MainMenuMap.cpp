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

	mainMenuCam->AddComponent<MainMenuHUD>();

	std::weak_ptr<clt::Sound> music = clt::Assets::Get().LoadAudio("Content/Resources/Audio/laink.mp3", "laink", AudioCategory::Music, false);

	clt::Audio::Get().PlaySound(music);
}

void MainMenuMap::Update()
{
}

void MainMenuMap::Close()
{
}
