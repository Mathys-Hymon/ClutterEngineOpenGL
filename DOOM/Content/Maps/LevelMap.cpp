#include "LevelMap.h"  
#include <Core/All.h>  
#include <Character/DoomController.h>
#include "Gameplay/Enemy/Zombie.h"

clt::Actor* camera;

clt::CubeActor* floorMesh;
clt::Actor* wallMesh;
clt::Actor* wall2;
clt::Actor* wall3;
clt::Actor* Ceiling;

Zombie* zombie1;
Zombie* zombie2;
Zombie* zombie3;

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

	clt::Assets::Get().LoadAudio("Content/Resources/Audio/inGame.mp3", "inGame", AudioCategory::Music);

	//clt::Audio::Get().SpawnSound("inGame");

	camera = AddActor<clt::Actor>("camera");

	camera->AddComponent<clt::CameraComponent>();
	camera->AddComponent<clt::BulletCollider>(ColliderShapeType::Box, Vector3{ 0.25f,1.5f,0.25f })->SetFriction(1.5f);
	camera->AddComponent < clt::BulletRigidBody> ()->LockRotation(true, true, false);
	camera->AddComponent<DoomController>();
	camera->SetActorLocation({ 10, 0, -12 });
	camera->SetActorRotation({ 0,180,0 });

	floorMesh = AddActor<clt::CubeActor>("floor", clt::Assets::Get().GetTexture("floor"), false, Vector2{100,100});
	floorMesh->SetActorTransform({ 0,-2 ,0 }, 0, {20,1,20});

	wallMesh = AddActor<clt::CubeActor>("wall", false);
	wallMesh->SetActorScale({ 10,2,1 });

	auto MIWall = clt::Assets::Get().CreateMaterialInstance("MI_Wall", wallMesh->GetComponentOfType<clt::MeshComponent>()->GetMesh().GetMaterial());
	wallMesh->SetActorLocation({ 2,0, -15 });

	zombie2 = AddActor<Zombie>("zombie2");
	zombie3 = AddActor<Zombie>("zombie3");

	zombie2->SetActorLocation({ 6, -0.3f, -3 });
	zombie3->SetActorLocation({ 1,-0.3f, -5 });

	zombie2->SetActorRotation({ 0,180,0 });

	wall2 = AddActor<clt::CubeActor>("wall2", false);
	wall2->SetActorScale({ 0.1,2,20 });

	wall2->GetComponentOfType<clt::MeshComponent>()->SetTexture("BaseColor", clt::Assets::Get().GetTexture("wall"), { 10, 75 });
	wall2->SetActorLocation({ -8,0, -10 });

	wall3 = AddActor<clt::CubeActor>("wall3", false);
	wall3->SetActorScale({ 0.1,2,20 });

	wall3->GetComponentOfType<clt::MeshComponent>()->SetTexture("BaseColor", clt::Assets::Get().GetTexture("wall"), { 10, 75 });
	wall3->SetActorLocation({ 8,0, -10 });


	Ceiling = AddActor<clt::CubeActor>("Ceiling", clt::Assets::Get().GetTexture("floor"), false, Vector2{ 100,100 });
	Ceiling->SetActorTransform({ 0,2 ,0 }, 0, { 20,1,20 });
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
