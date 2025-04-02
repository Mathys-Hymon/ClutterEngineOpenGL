#include "LevelMap.h"  
#include <Core/All.h>  
#include <Character/DoomController.h>

clt::Actor* camera;

LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	std::vector<clt::Texture*> weapon =  clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4,"_playerShoot.png", "playerShoot", TextureFilter::NEAREST);
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball");
	weapon.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/playerWeapon.png", "weapon"));

	clt::Assets::Get().LoadFont("Content/Resources/Font/ClassicFont.ttf", "Classic");

	camera = AddActor<clt::Actor>("camera");
	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent<DoomController>();
	camera->SetActorLocation({ 0, 0, 5 });

	camera->AddComponent<clt::HUDComponent>()->CreateWidget<clt::UIPanel>("PlayerScreen");
	camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::FlipbookElement>("mainWeapon", weapon, true, 5);
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
