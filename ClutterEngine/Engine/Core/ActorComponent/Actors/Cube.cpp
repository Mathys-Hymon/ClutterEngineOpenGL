#include "pch.h"
#include <Core/ActorComponent/Actors/Cube.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

Cube::Cube(std::string name) : Actor(name)
{
	Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube");
	AddComponent<MeshComponent>(clt::Assets::Get().GetMesh("cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(std::string name, std::string texture) : Actor(name)
{
	Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", texture);
	AddComponent<MeshComponent>(clt::Assets::Get().GetMesh("cube"));
	AddComponent<OBBCollider>();
}

Cube::Cube(std::string name, Texture* texture) : Actor(name)
{
	Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", {texture});
	AddComponent<MeshComponent>(clt::Assets::Get().GetMesh("cube"));
	AddComponent<OBBCollider>();
}
