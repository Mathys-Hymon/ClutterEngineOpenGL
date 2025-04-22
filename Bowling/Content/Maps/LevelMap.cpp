#include "LevelMap.h"  
#include <Core/All.h>  
#include "Gameplay/BowlingLane.h"

clt::Actor* camera;  

BowlingLane* lane1;
clt::CubeActor* ceiling;

clt::Actor* ball;  


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
clt::Assets::Get().LoadTexture("Content/Resources/Sprites/woodFloor.png", "floor");
clt::Assets::Get().LoadTexture("Content/Resources/Sprites/DecoBanner.png", "banner");

clt::Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "ball");
clt::Assets::Get().LoadMesh("Content/Resources/Mesh/pin.obj", "pin", "pinTexture", false);

clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
clt::Input::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "MovementVertical");

camera = AddActor<clt::Actor>("camera");
camera->AddComponent<clt::CameraComponent>();
//camera->AddComponent<clt::CameraController>("PlayerMovement", "MovementVertical", 10);
camera->SetActorLocation({ -1.5f, -0.6f, -13 });
camera->SetActorRotation({ 0,180,0 });

lane1 = AddActor<BowlingLane>("manager", false, Vector3{ 0, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 6, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 12, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 18, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -6, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -12, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -18, 0, 0 });

ceiling = AddActor<clt::CubeActor>("ceiling");
//ceiling->RemoveComponent<clt::OBBCollider>();
ceiling->SetActorLocation({0,5,0});
ceiling->SetActorScale({ 50,0.1f,50 });

}  

void LevelMap::Update()  
{
}  

void LevelMap::Close()  
{  
}
