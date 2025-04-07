#include "DefaultMap.h"
#include <Core/All.h>

clt::Actor* camera;

DefaultMap::DefaultMap(std::string pName) : clt::Level(pName)
{
}

DefaultMap::~DefaultMap()
{
}

void DefaultMap::Load()
{
	camera = AddActor<clt::Actor>("camera");
	camera->AddComponent<clt::CameraComponent>();
}

void DefaultMap::Update()
{
}

void DefaultMap::Close()
{
}