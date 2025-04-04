#include "pch.h"
#include <Core/ActorComponent/Actors/Cube.h>
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

Cube::Cube(Level* pLevel, std::string name, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"), 0, mTiling);
	AddComponent<OBBCollider>();
}

Cube::Cube(Level* pLevel, const char* name, Vector2 mTiling) : Actor(pLevel, std::string(name))
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"), 0, mTiling);
	AddComponent<OBBCollider>();
}

Cube::Cube(Level* pLevel, std::string name, std::string texture, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"), 0, mTiling);
	AddComponent<OBBCollider>();
	GetComponentOfType<MeshComponent>()->SetTexture(texture);
}

Cube::Cube(Level* pLevel, std::string name, Texture* texture, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube"), 0, mTiling);
	AddComponent<OBBCollider>();
	GetComponentOfType<MeshComponent>()->SetTexture(texture);
}
