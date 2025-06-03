#include "DefaultMap.h"  
#include <Enviro/Water.h>
#include <Core/All.h>

clt::Actor* camera;

Water* water;
clt::CubeActor* test;

float basicTimer = 0;

DefaultMap::DefaultMap(std::string pName) : clt::Level(pName)
{
}

DefaultMap::~DefaultMap()
{
}

void DefaultMap::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/metalFloor.png", "floor", TextureFilter::NEAREST);

	//camera = AddActor<clt::Actor>("camera");
	//camera->SetActorLocation({ 10, 0, -12 });
	//camera->SetActorRotation({ 0,180,0 });

	//camera->AddComponent<clt::CameraComponent>();
	//camera->AddComponent < clt::FPSController >();
	//camera->SetActorLocation({ 0, 0, 5 });

	water = AddActor<Water>("water");
	water->SetActorRotation({ 90,0,0 });
	
	//test = AddActor<clt::CubeActor>("test");
}

void DefaultMap::Update()
{
}

void DefaultMap::Close()
{
}
