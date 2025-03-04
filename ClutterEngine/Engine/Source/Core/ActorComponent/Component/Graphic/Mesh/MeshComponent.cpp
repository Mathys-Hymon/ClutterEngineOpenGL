#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(int pDrawOrder) : Component(pDrawOrder), mMesh(nullptr), mTextureIndex(0)
{
    mMesh = new Mesh();
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
        Matrix4Row wt = mOwner->getTransform().GetMat4Transform();
        mMesh->GetShader().Use();
        mMesh->GetShader().SetMat4Row("uViewProj", viewProj);
        mMesh->GetShader().SetMat4Row("uWorldTransform", wt);
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if (t) t->Bind();
        mMesh->GetVAO();
        glDrawElements(GL_TRIANGLES, mMesh->GetVAO().GetIndicesCount(), GL_UNSIGNED_INT, nullptr);

        if (t) t->UnBind();
    }

}
