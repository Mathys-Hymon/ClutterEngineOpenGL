#include "LevelMap.h"  
#include <Core/All.h>  
#include "Gameplay/BowlingLane.h"
#include "Character/BowlingController.h"
#include "Gameplay/BowlingBall.h"

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

AddActor<BowlingBall>("ball");

camera = AddActor<clt::Actor>("camera");

camera->AddComponent<clt::CameraComponent>();
camera->AddComponent<clt::HUDComponent>();
camera->AddComponent<BowlingController>();
camera->SetActorLocation({ -1.5f, -0.6f, -13 });
camera->SetActorRotation({ 0,180,0 });

GetActorOfType<BowlingBall>()->SetActorLocation(camera->GetActorLocation() + Vector3{ 0,-0.5f,1 });

lane1 = AddActor<BowlingLane>("manager", false, Vector3{ 0, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 6, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 12, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ 18, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -6, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -12, 0, 0 });
AddActor<BowlingLane>("manager", true, Vector3{ -18, 0, 0 });

ceiling = AddActor<clt::CubeActor>("ceiling");
ceiling->SetActorLocation({0,5,0});
ceiling->SetActorScale({ 50,0.1f,50 });

}  

void LevelMap::Update()  
{
}  

void LevelMap::Close()  
{  
}
