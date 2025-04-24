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

	clt::Assets::Get().LoadFont("Content/Resources/Font/DooM.ttf", "doomFont");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/metalFloor.png", "floor", TextureFilter::NEAREST);

	camera = AddActor<clt::Actor>("camera");

	floorMesh = AddActor<clt::CubeActor>("floor");
	wallMesh = AddActor<clt::CubeActor>("wall", true);
	wallMesh->SetActorLocation({ 2,0 });

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent<DoomController>();
	camera->SetActorLocation({ 0, 0, 5 });
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
