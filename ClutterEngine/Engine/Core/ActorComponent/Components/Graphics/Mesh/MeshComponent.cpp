#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>

using namespace clt;

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder), mMesh(pMesh)
{
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, int pDrawOrder, Vector2 pTextureTiling) : Component(pDrawOrder)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, std::weak_ptr<IMaterial>, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder), mMesh(pMesh)
{
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, std::weak_ptr<IMaterial>, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
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
        auto mat = mMaterial.lock() ? mMaterial.lock().get() : temp->GetMaterial().lock().get();

        mat->GetShader()->Use();
        mat->SetMat4Row("uViewProj", viewProj);
        temp->GetVAO().Bind();

        Matrix4Row wt = GetWorldTransform().GetMat4Transform();
        mat->SetMat4Row("uWorldTransform", wt);

        mat->Apply();

        glDrawArrays(temp->GetTesselated() ? GL_PATCHES : GL_TRIANGLES, 0, temp->GetVAO().GetVerticeCount());
    }
}

void MeshComponent::SetTexture(std::string textureName, std::weak_ptr<Texture> texture, Vector2 tiling)
{
    mMesh.lock()->GetMaterialRef().SetTexture(textureName, texture);
    mMesh.lock()->GetMaterialRef().SetVec2("uTiling", tiling);
}    
     
void MeshComponent::SetTexture(std::string textureName, std::string& texture, Vector2 tiling)
{
    std::weak_ptr<Texture> tempTexture = Assets::Get().GetTexture(texture);
    mMesh.lock()->GetMaterialRef().SetTexture(textureName, tempTexture);
    mMesh.lock()->GetMaterialRef().SetVec2("uTiling", tiling);
}