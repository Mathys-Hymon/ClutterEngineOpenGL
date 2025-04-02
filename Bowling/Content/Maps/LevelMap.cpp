#include "LevelMap.h"  
#include <Core/All.h>  

clt::Actor* camera;  

clt::Actor* pin;

std::vector<clt::Actor*> pins;  

clt::Actor* ball;  

clt::Cube* floorBlock;  

LevelMap::LevelMap(std::string pName) : clt::Level(pName)  
{  
}  

LevelMap::~LevelMap()  
{  
}  

void LevelMap::Load()  
{  
clt::Assets::Get().LoadTexture("Content/Resources/Sprites/ballTexture.png", "ballTexture");
clt::Assets::Get().LoadTexture("Content/Resources/Sprites/pinMat.png", "pinTexture");

clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball");
clt::Assets::Get().LoadMesh("Content/Resources/Mesh/pin.obj", "pin", "pinTexture");

clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
clt::Input::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "MovementVertical");

int maxRow = 5;  
//
//for (int row = 1; row <= maxRow; row++)  
//{  
//	for (int col = 1; col < row; col++)  
//	{  
//		std::string tempName = "pin_" + std::to_string(pins.size());
//
//		clt::Actor* tempActor = AddActor<clt::Actor>(tempName);
//		tempActor->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("pin"));
//		tempActor->AddComponent<clt::OBBCollider>(Vector3{ 10, 20, 10 });
//		tempActor->GetComponentOfType<clt::OBBCollider>()->SetRelativeLocation({ 0, 0.2f, 0 });
//		tempActor->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.5f;
//		tempActor->AddComponent<clt::RigidBody>()->mLockRotation = false;
//		tempActor->SetActorScale(0.1f);
//
//		float x = (static_cast<float>(col * 2) / static_cast<float>(row));
//		float y = - 1.6f;
//		float z = -static_cast<float>(row) / 4;
//		
//		tempActor->SetActorLocation({ x ,y, z });
//
//		pins.push_back(tempActor);
//	}  
//}  

camera = AddActor<clt::Actor>("camera");
camera->AddComponent<clt::CameraComponent>();

camera->AddComponent<clt::CameraController>("PlayerMovement", "MovementVertical");

ball = AddActor<clt::Actor>("ball");  

floorBlock = AddActor<clt::Cube>("floor");  

camera->SetActorLocation({ 0, 0, 5 });

ball->AddComponent<clt::MeshComponent>(clt::Assets::Get().GetMesh("ball"));  
ball->AddComponent<clt::SphereCollider>();  
ball->GetComponentOfType<clt::SphereCollider>()->mFriction = 0.1f;
ball->AddComponent<clt::RigidBody>()->mLockRotation = false;  

floorBlock->AddComponent<clt::OBBCollider>();  
floorBlock->GetComponentOfType<clt::OBBCollider>()->mFriction = 0.1f;


floorBlock->SetActorScale({ 5, 0.3f, 5 });  
floorBlock->SetActorLocation({ 0, -2, 0 });  

ball->SetActorScale(0.1f);  
ball->SetActorLocation({ -1, -1.3f, 0.75f });  

ball->GetComponentOfType<clt::RigidBody>()->SetVelocity({ 250, 0, 0 });

ball->SetActorRotation(23);
}  

void LevelMap::Update()  
{
	//ball->AddActorRotationOffset(2);
}  

void LevelMap::Close()  
{  
}
