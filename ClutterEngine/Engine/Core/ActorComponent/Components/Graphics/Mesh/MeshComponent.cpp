#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(Mesh* pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(pMesh), mTextureIndex(0)
{
    if (mMesh) mMesh->SetTextureTiling(pTextureTiling);
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
        mMesh->GetShader().SetVec2f("uTiling", mMesh->GetTextureTiling());
        mMesh->GetTexture(mTextureIndex)->Bind();

        glDrawArrays(mMesh->GetTesselated() ? GL_PATCHES : GL_TRIANGLES, 0, mMesh->GetVAO().GetVerticeCount());
    }
}

void MeshComponent::SetTexture(Texture* texture, size_t index)
{
    mMesh->SetTexture(texture, index);
}    
     
void MeshComponent::SetTexture(std::string& texture, size_t index)
{
    mMesh->SetTexture(texture, index);
}

void MeshComponent::SetTextureIndex(size_t pTextureIndex)
{
    mTextureIndex = pTextureIndex;
}
