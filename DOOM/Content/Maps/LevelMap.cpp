#include "LevelMap.h"  
#include <Core/All.h>  
#include <Character/DoomController.h>

clt::Actor* camera;

clt::Actor* floorMesh;
clt::Actor* wallMesh;

LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	std::vector<clt::Texture*> weapon =  clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4,"_playerShoot.png", "playerShoot", TextureFilter::NEAREST);
	weapon.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/playerWeapon.png", "weapon", TextureFilter::NEAREST));

	clt::Assets::Get().LoadFont("Content/Resources/Font/RoadPixel.ttf", "Classic");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/metalFloor.png", "floor", TextureFilter::NEAREST);

	camera = AddActor<clt::Actor>("camera");

	floorMesh = AddActor<clt::CubeActor>("floor");
	wallMesh = AddActor<clt::CubeActor>("wall", true);
	wallMesh->SetActorLocation({ 2,0 });

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent<DoomController>();
	camera->SetActorLocation({ 0, 0, 5 });

	camera->AddComponent<clt::HUDComponent>()->CreateWidget<clt::UIPanel>("PlayerScreen");
	camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::FlipbookElement>("mainWeapon", weapon, true, 5);

	camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::TextElement>("lifeText", "Bonjour a tous la team", Color::olive, 1);
	camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::SpriteElement>("sprite", "floor");
}

void LevelMap::Update()
{

	//clt::DebugDraw::Get().DrawBox({ 3,0,0 }, {1,1,1});
}

void LevelMap::Close()
{
}
