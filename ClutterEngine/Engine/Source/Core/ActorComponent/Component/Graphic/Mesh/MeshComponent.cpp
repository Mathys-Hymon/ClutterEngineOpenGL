#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(Mesh* pMesh, int pDrawOrder) : Component(pDrawOrder), mMesh(nullptr), mTextureIndex(0)
{
    if (pMesh)
    {
        mMesh = pMesh;
    }
    else
    {
        mMesh = new Mesh();
    }
}

MeshComponent::MeshComponent(Texture* pTexture, int pDrawOrder) : Component(pDrawOrder), mMesh(nullptr), mTextureIndex(0)
{
        mMesh = new Mesh();
        mMesh->AddTexture(pTexture);
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
        mMesh->GetShader().Use();
        mMesh->GetShader().SetMat4Row("uViewProj", viewProj);
        mMesh->GetVAO().Bind();

        Matrix4Row wt = GetWorldTransform().GetMat4Transform();
        mMesh->GetShader().SetMat4Row("uWorldTransform", wt);
        mMesh->GetTexture(mTextureIndex)->Bind();
        glDrawElements(GL_TRIANGLES, mMesh->GetVAO().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
    mTextureIndex = pTextureIndex;
}
