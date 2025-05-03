#include "LevelMap.h"  
#include <Core/All.h>  
#include <Character/DoomController.h>

clt::Actor* camera;

clt::CubeActor* floorMesh;
clt::Actor* wallMesh;
clt::Actor* wall2;
clt::Actor* wall3;
clt::Actor* Ceiling;

LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{

	clt::Assets::Get().LoadFont("Content/Resources/Font/DooM.ttf", "doomFont");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/floor.png", "floor", TextureFilter::NEAREST);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/wall.png", "wall", TextureFilter::NEAREST);

	camera = AddActor<clt::Actor>("camera");

	floorMesh = AddActor<clt::CubeActor>("floor", clt::Assets::Get().GetTexture("floor"), false, Vector2{100,100});
	floorMesh->SetActorTransform({ 0,-2 ,0 }, 0, {20,1,20});

	wallMesh = AddActor<clt::CubeActor>("wall", false);
	wallMesh->SetActorScale({ 10,2,1 });

	wallMesh->GetComponentOfType<clt::MeshComponent>()->SetTexture(clt::Assets::Get().GetTexture("wall"), {10, 75});
	wallMesh->SetActorLocation({ 2,0, -15 });



	wall2 = AddActor<clt::CubeActor>("wall2", false);
	wall2->SetActorScale({ 0.1,2,20 });

	wall2->GetComponentOfType<clt::MeshComponent>()->SetTexture(clt::Assets::Get().GetTexture("wall"), { 10, 75 });
	wall2->SetActorLocation({ -8,0, -10 });

	wall3 = AddActor<clt::CubeActor>("wall3", false);
	wall3->SetActorScale({ 0.1,2,20 });

	wall3->GetComponentOfType<clt::MeshComponent>()->SetTexture(clt::Assets::Get().GetTexture("wall"), { 10, 75 });
	wall3->SetActorLocation({ 8,0, -10 });


	Ceiling = AddActor<clt::CubeActor>("Ceiling", clt::Assets::Get().GetTexture("floor"), false, Vector2{ 100,100 });
	Ceiling->SetActorTransform({ 0,2 ,0 }, 0, { 20,1,20 });



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
