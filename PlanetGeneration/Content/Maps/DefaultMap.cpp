#include "DefaultMap.h"  
#include <Core/All.h>

clt::Actor* camera;

clt::Actor* planet;

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

	camera = AddActor<clt::Actor>("camera");
	camera->SetActorLocation({ 10, 0, -12 });
	camera->SetActorRotation({ 0,180,0 });

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent < clt::FPSController > ();
	camera->SetActorLocation({ 0, 0, 5 });

	planet = AddActor<clt::Actor>("planet");
	planet->AddComponent<clt::MeshComponent>()
}

void DefaultMap::Update()
{
	clt::DebugDraw::Get().DrawBox({ 3,0,0 }, { 1,1,1 });
}

void DefaultMap::Close()
{
}
