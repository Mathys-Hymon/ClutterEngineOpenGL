#include "LevelMap.h"
#include <Core/All.h>

clt::Actor* camera;
clt::Actor* pin;

clt::Actor* ball;

clt::Actor* floorBlock;

LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/pinTexture.png", "pinTexture");

	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/pin.obj", "pin");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "floor");

	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "MovementVertical");


	camera = AddActor(new clt::Actor("camera"));
	camera->AddComponent<clt::CameraController>("PlayerMovement", "MovementVertical");

	pin = AddActor(new clt::Actor("pin"));

	ball = AddActor(new clt::Actor("ball"));

	floorBlock = AddActor(new clt::Actor("floor"));

	camera->AddComponent<clt::CameraComponent>();
	camera->SetActorLocation({ 0, 0, 5 });

	pin->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("pin"));
	pin->AddComponent<clt::OBBCollider>(Vector3{ 10, 30, 10 });
	pin->AddComponent<clt::RigidBody>();

	ball->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("ball"));
	ball->AddComponent<clt::OBBCollider>();
	ball->AddComponent<clt::RigidBody>();

	floorBlock->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("floor"));
	floorBlock->AddComponent<clt::OBBCollider>();

	pin->SetActorScale(0.1f);
	pin->SetActorLocation({ 0, 1, 0.5 });

	floorBlock->SetActorScale({ 5, 0.3f, 5 });
	floorBlock->SetActorLocation({ 0, -2, 0 });

	ball->SetActorScale(0.1f);
	ball->SetActorLocation({ -1, 1, 0});

}

void LevelMap::Update()
{
	ball->GetComponentOfType<clt::RigidBody>()->AddVelocity({ 1, 0, 0 });

	ball->AddActorRotationOffset(-1);
}

void LevelMap::Close()
{
}
