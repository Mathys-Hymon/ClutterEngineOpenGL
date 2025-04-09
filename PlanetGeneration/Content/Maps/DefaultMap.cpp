#include "DefaultMap.h"  
#include <Core/All.h>

clt::Actor* camera;

clt::Actor* floorMesh;
clt::Actor* wallMesh;

float basicTimer = 0;

DefaultMap::DefaultMap(std::string pName) : clt::Level(pName)
{
}

DefaultMap::~DefaultMap()
{
}

void DefaultMap::Load()
{
	std::vector<clt::Texture*> weapon = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4, "_playerShoot.png", "playerShoot", TextureFilter::NEAREST);
	weapon.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/playerWeapon.png", "weapon", TextureFilter::NEAREST));

	clt::Assets::Get().LoadFont("Content/Resources/Font/ClassicFont.ttf", "Classic");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/metalFloor.png", "floor", TextureFilter::NEAREST);

	camera = AddActor<clt::Actor>("camera");

	floorMesh = AddActor<clt::CubeActor>("floor");
	wallMesh = AddActor<clt::CubeActor>("wall", true);
	wallMesh->SetActorLocation({ 2,0 });

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent < clt::FPSController > ();
	camera->SetActorLocation({ 0, 0, 5 });

	camera->AddComponent<clt::HUDComponent>()->CreateWidget<clt::UIPanel>("PlayerScreen");
	camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::FlipbookElement>("mainWeapon", weapon, true, 5);

	//camera->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::TextElement>("lifeText", "Hello world !","Classic");

}

void DefaultMap::Update()
{

	clt::DebugDraw::Get().DrawBox({ 3,0,0 }, { 1,1,1 });

	if (basicTimer < 3) basicTimer += clt::Timer::deltaTime;
	else
	{
		if (floorMesh)
		{
			DestroyActor<clt::CubeActor>(floorMesh);
		}
	}
}

void DefaultMap::Close()
{
}
