#include "LevelMap.h"  
#include <Core/All.h>

clt::CubeActor* floorActor;

clt::CubeActor* fallingCubes;

LevelMap::LevelMap(std::string pName) : clt::Level(pName), tempTime(0)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	floorActor = AddActor<clt::CubeActor>("floor", clt::Assets::Get().GetTexture("floor"), false, Vector2{ 100,100 });
	floorActor->AddComponent < clt::BulletRigidBody>(clt::rbState::Static);
	//floorActor->SetActorTransform({ 0,-2 ,0 }, 0, { 20,1,20 });
	floorActor->SetActorLocation({ 0, -50,0 });

	fallingCubes = AddActor<clt::CubeActor>("floor", clt::Assets::Get().GetTexture("floor"), false, Vector2{ 100,100 });
	fallingCubes->SetActorLocation({ 0,100,0 });
	fallingCubes->AddComponent < clt::BulletRigidBody>();
}

void LevelMap::Update()
{
	if (tempTime <= 2.0f) tempTime += clt::Timer::deltaTime;

	else
	{
		tempTime = 0;

		//std::string name = "actor " + Maths::Rand(0, 100);

		auto temp = AddActor<clt::CubeActor>("test");
		temp->SetActorLocation({ Maths::Rand(-2.0f,2.0f), 100, Maths::Rand(-2.0f,2.0f) });
		temp->AddComponent<clt::BulletRigidBody>();
	}
}

void LevelMap::Close()
{
}
