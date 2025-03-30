#include "pch.h"
#include <Core/ActorComponent/Actors/Cube.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

Cube::Cube(std::string name) : Actor(name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(const char* name) : Actor(std::string(name))
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(std::string name, std::string texture) : Actor(name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(std::string name, Texture* texture) : Actor(name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"));
	AddComponent<OBBCollider>();
}
