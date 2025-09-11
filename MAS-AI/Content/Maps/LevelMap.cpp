#include "LevelMap.h"  
#include <Core/All.h>

clt::Actor* camera;

LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
	camera = AddActor<clt::Actor>("camera");

	camera->AddComponent<clt::CameraComponent>(70, ProjectionMode::Orthographic);
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
