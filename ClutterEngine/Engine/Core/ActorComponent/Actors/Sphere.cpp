#include "pch.h"
#include "Sphere.h"
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

Sphere::Sphere(Level* pLevel, const char* name, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "sphere"), 0, mTiling);
	AddComponent<SphereCollider>();
}

Sphere::Sphere(Level* pLevel, std::string name, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "sphere"), 0, mTiling);
	AddComponent<SphereCollider>();
}

Sphere::Sphere(Level* pLevel, std::string name, std::string texture, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "sphere"), 0, mTiling);
	AddComponent<SphereCollider>();
}

Sphere::Sphere(Level* pLevel, std::string name, Texture* texture, Vector2 mTiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/sphere.obj", "sphere"), 0, mTiling);
	AddComponent<SphereCollider>();
}
