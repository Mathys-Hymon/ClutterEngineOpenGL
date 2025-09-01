#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(pMesh)
{
    if (mMesh.lock()) mMesh.lock().get()->GetMaterial().SetInt("");
    mMesh.lock()->GetMaterial().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(nullptr)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    mMesh.lock()->GetMaterial().SetVec2("uTiling", pTextureTiling);
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
    auto temp = mMesh.lock();
    if (temp)
    {
        temp->GetMaterial().GetShader()->Use();
        temp->GetMaterial().SetMat4Row("uViewProj", viewProj);
        temp->GetVAO().Bind();

        Matrix4Row wt = GetWorldTransform().GetMat4Transform();
        temp->GetMaterial().SetMat4Row("uWorldTransform", wt);

        temp->GetMaterial().Apply();

        glDrawArrays(temp->GetTesselated() ? GL_PATCHES : GL_TRIANGLES, 0, temp->GetVAO().GetVerticeCount());
    }
}

void MeshComponent::SetTexture(std::string textureName, std::weak_ptr<Texture> texture, Vector2 tiling)
{
    mMesh.lock()->GetMaterial().SetTexture(textureName, texture);
    mMesh.lock()->GetMaterial().SetVec2("uTiling", tiling);
}    
     
void MeshComponent::SetTexture(std::string textureName, std::string& texture, Vector2 tiling)
{
    std::weak_ptr<Texture> tempTexture = Assets::Get().GetTexture(texture);
    mMesh.lock()->GetMaterial().SetTexture(textureName, tempTexture);
    mMesh.lock()->GetMaterial().SetVec2("uTiling", tiling);
}