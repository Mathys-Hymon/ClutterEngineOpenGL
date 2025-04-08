#include "pch.h"
#include "CubeActor.h"
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

CubeActor::CubeActor(Level* pLevel, const char* name, const Vector2& tiling, bool tesselate) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}

CubeActor::CubeActor(Level* pLevel, const char* name, bool tesselate, const Vector2& tiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}

CubeActor::CubeActor(Level* pLevel, std::string name, const Vector2& tiling, bool tesselate) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}

CubeActor::CubeActor(Level* pLevel, std::string name, bool tesselate, const Vector2& tiling) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}

CubeActor::CubeActor(Level* pLevel, std::string name, std::string texture, const Vector2& tiling, bool tesselate) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}

CubeActor::CubeActor(Level* pLevel, std::string name, Texture* texture, const Vector2& tiling, bool tesselate) : Actor(pLevel, name)
{
	AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", tesselate), 0, tiling);
	AddComponent<OBBCollider>();
}
