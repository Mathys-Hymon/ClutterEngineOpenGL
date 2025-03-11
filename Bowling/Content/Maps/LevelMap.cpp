#include "LevelMap.h"



LevelMap::LevelMap(std::string pName) : clt::Level(pName)
{
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/ball.obj", "ball");
	clt::Assets::Get().LoadMesh("Content/Resources/Mesh/pin.obj", "pin");
}

LevelMap::~LevelMap()
{
}

void LevelMap::Load()
{
}

void LevelMap::Update()
{
}

void LevelMap::Close()
{
}
