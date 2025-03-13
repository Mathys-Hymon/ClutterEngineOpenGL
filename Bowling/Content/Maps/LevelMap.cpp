#include "LevelMap.h"  
#include <Core/All.h>  

clt::Actor* camera;  

clt::Actor* pin;

std::vector<clt::Actor*> pins;  

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

int maxRow = 1;  

for (int row = 1; row <= maxRow; row++)  
{  
	for (int col = 1; col < row; col++)  
	{  
		std::string tempName = "pin_" + std::to_string(pins.size());

		clt::Actor* tempActor = AddActor(new clt::Actor(tempName));
		tempActor->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("pin"));
		tempActor->AddComponent<clt::OBBCollider>(Vector3{ 10, 20, 10 });
		tempActor->GetComponentOfType<clt::OBBCollider>()->SetRelativeLocation({ 0, 0.2f, 0 });
		tempActor->AddComponent<clt::RigidBody>()->mLockRotation = false;
		tempActor->SetActorScale(0.1f);

		tempActor->SetActorLocation({ static_cast<float>(row) / 4, -1.6f, (static_cast<float>(col * 1.5f) / static_cast<float>(row))});

		pins.push_back(tempActor);
	}  
}  

camera = AddActor(new clt::Actor("camera"));  
camera->AddComponent<clt::CameraController>("PlayerMovement", "MovementVertical");

ball = AddActor(new clt::Actor("ball"));  

floorBlock = AddActor(new clt::Actor("floor"));  

camera->AddComponent<clt::CameraComponent>();  
camera->SetActorLocation({ 0, 0, 5 });  

ball->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("ball"));  
ball->AddComponent<clt::OBBCollider>();  
ball->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.1f;  
ball->AddComponent<clt::RigidBody>()->mLockRotation = false;  

floorBlock->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("floor"));  
floorBlock->AddComponent<clt::OBBCollider>();  
floorBlock->GetComponentOfType<clt::OBBCollider>()->mFriction = 5;


floorBlock->SetActorScale({ 5, 0.3f, 5 });  
floorBlock->SetActorLocation({ 0, -2, 0 });  

ball->SetActorScale(0.1f);  
ball->SetActorLocation({ -1, -1.3f, 0.75f });  

ball->GetComponentOfType<clt::RigidBody>()->SetVelocity({ 250, 0, 0 });

ball->SetActorRotation(23);
}  

void LevelMap::Update()  
{
}  

void LevelMap::Close()  
{  
}
