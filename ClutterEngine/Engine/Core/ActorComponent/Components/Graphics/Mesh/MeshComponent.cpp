#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(Mesh* pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(pMesh), mTextureTiling(pTextureTiling), mTexture(nullptr)
{
    if (mMesh) mMesh->SetTextureTiling(pTextureTiling);
    mMesh->GetMaterial().SetVec2f("uTiling", mTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(nullptr), mTextureTiling(pTextureTiling), mTexture(nullptr)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    mMesh->GetMaterial().SetVec2f("uTiling", mTextureTiling);
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
        mMesh->GetMaterial().Use();
        mMesh->GetMaterial().SetMat4Row("uViewProj", viewProj);
        mMesh->GetVAO().Bind();

        Matrix4Row wt = GetWorldTransform().GetMat4Transform();
        mMesh->GetMaterial().SetMat4Row("uWorldTransform", wt);

        auto* tex = mTexture;
        if (tex) mTexture->Bind();
        else mMesh->GetTexture(0)->Bind();

        glDrawArrays(mMesh->GetTesselated() ? GL_PATCHES : GL_TRIANGLES, 0, mMesh->GetVAO().GetVerticeCount());
    }
}

void MeshComponent::SetTexture(Texture* texture, Vector2 tiling)
{
    mTexture = texture;
    mTextureTiling = tiling;
    mMesh->GetMaterial().SetVec2f("uTiling", mTextureTiling);
}    
     
void MeshComponent::SetTexture(std::string& texture, Vector2 tiling)
{
    mTexture = Assets::Get().GetTexture(texture);
    mTextureTiling = tiling;
    mMesh->GetMaterial().SetVec2f("uTiling", mTextureTiling);
}