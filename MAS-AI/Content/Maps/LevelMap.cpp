#include "LevelMap.h"  
#include <Core/All.h>

#include "Core/ActorComponent/Components/Graphics/Particle/ParticleComponent.h"

clt::Actor* dummy;

LevelMap::LevelMap(std::string pName) : clt::Level(pName), tempTime(0)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	dummy = AddActor<clt::Actor>("dummy");
	dummy->AddComponent < clt::ParticleComponent>();
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
