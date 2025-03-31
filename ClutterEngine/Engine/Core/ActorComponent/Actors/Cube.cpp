#include "pch.h"
#include <Core/ActorComponent/Actors/Cube.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

Cube::Cube(Level* pLevel, std::string name) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(Level* pLevel, const char* name) : Actor(pLevel, std::string(name))
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(Level* pLevel, std::string name, std::string texture) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(Level* pLevel, std::string name, Texture* texture) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}
