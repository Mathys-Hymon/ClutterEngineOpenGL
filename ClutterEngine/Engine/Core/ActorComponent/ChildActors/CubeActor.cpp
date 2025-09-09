#include "pch.h"  
#include "CubeActor.h"  
#include <Core/ActorComponent/Components/Physics/Collisions/OBBCollider.h>  
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>  
#include <Core/Assets/Assets.h>  

using namespace clt;  

CubeActor::CubeActor(Level* pLevel, std::string pName, Vector2 pTiling, bool pTesselate) : Actor(pLevel, pName)  
{  
   AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", pTesselate), 0, pTiling);  
   AddComponent<OBBCollider>();  
}  

CubeActor::CubeActor(Level* pLevel, std::string pName, bool pTesselate, Vector2 pTiling) : Actor(pLevel, pName)  
{  
   AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", pTesselate), 0, pTiling);  
   AddComponent<OBBCollider>();  
}  

CubeActor::CubeActor(Level* pLevel, std::string pName, std::string pTexture, bool pTesselate, Vector2 pTiling) : Actor(pLevel, pName)  
{  
   AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", pTexture, pTesselate), 0, pTiling);  
   AddComponent<OBBCollider>();  
}  

CubeActor::CubeActor(Level* pLevel, std::string pName, std::weak_ptr<clt::Texture> pTexture, bool pTesselate, Vector2 pTiling) : Actor(pLevel, pName)
{  
   AddComponent<MeshComponent>(Assets::Get().LoadMesh("Content/Resources/Mesh/cube.obj", "cube", std::vector<std::weak_ptr<clt::Texture>>{pTexture}, pTesselate), 0, pTiling);  
   AddComponent<OBBCollider>();  
}