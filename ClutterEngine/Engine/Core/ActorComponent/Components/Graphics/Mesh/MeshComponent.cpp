#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(Mesh* pMesh, int pDrawOrder) : Component(pDrawOrder), mMesh(pMesh), mTextureIndex(0)
{}

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
        glDrawArrays(GL_TRIANGLES, 0, 8);
    }

}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
    mTextureIndex = pTextureIndex;
}
