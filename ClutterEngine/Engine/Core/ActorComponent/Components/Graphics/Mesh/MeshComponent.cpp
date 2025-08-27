#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(Mesh* pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(pMesh)
{
    if (mMesh) mMesh->SetTextureTiling(pTextureTiling);
    mMesh->GetMaterial().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(nullptr)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    mMesh->GetMaterial().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::~MeshComponent()
{
    if (mOwner) mOwner->GetLevel()->GetRenderer().RemoveMeshComponent(this);
}

void MeshComponent::SetOwner(Actor* pOwner)
{
    Component::SetOwner(pOwner);
    mOwner->GetLevel()->GetRenderer().AddMeshComponent(this);
}

void MeshComponent::Draw(Matrix4Row viewProj)
{
    if (mMesh)
    {
        mMesh->GetMaterial().GetShader()->Use();
        mMesh->GetMaterial().SetMat4Row("uViewProj", viewProj);
        mMesh->GetVAO().Bind();

        Matrix4Row wt = GetWorldTransform().GetMat4Transform();
        mMesh->GetMaterial().SetMat4Row("uWorldTransform", wt);

        mMesh->GetMaterial().Apply();

        glDrawArrays(mMesh->GetTesselated() ? GL_PATCHES : GL_TRIANGLES, 0, mMesh->GetVAO().GetVerticeCount());
    }
}

void MeshComponent::SetTexture(std::string textureName, Texture* texture, Vector2 tiling)
{
    mMesh->GetMaterial().SetTexture(textureName, texture);
    mMesh->GetMaterial().SetVec2("uTiling", tiling);
}    
     
void MeshComponent::SetTexture(std::string textureName, std::string& texture, Vector2 tiling)
{
    Texture* tempTexture = Assets::Get().GetTexture(texture);
    mMesh->GetMaterial().SetTexture(textureName, tempTexture);
    mMesh->GetMaterial().SetVec2("uTiling", tiling);
}