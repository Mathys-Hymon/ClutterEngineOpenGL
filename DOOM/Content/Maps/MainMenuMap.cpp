#include "MainMenuMap.h"
#include "Core/All.h"

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

}

void MainMenuMap::Update()
{
}

void MainMenuMap::Close()
{
}
