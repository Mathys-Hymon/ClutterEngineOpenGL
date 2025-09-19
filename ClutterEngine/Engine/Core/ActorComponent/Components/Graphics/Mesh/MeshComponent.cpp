#include "pch.h"
#include <Core/Levels/Level.h>
#include <Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>
#include <Core/Assets/Assets.h>

using namespace clt;

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder), mMesh(pMesh)
{
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    if (mMesh.lock())   mMesh.lock()->GetMaterialRef().SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, std::shared_ptr<IMaterial> material, Vector2 pTextureTiling, int pDrawOrder) : 
    Component(pDrawOrder), mMesh(pMesh), mMaterial(material)
{
    mMaterial->SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(const std::string& pMesh, std::shared_ptr<IMaterial> material, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder), mMaterial(material)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    mMaterial->SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, std::weak_ptr<Texture> texture, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder), mMesh(pMesh)
{
    SetTexture("BaseColor", texture);
}

MeshComponent::MeshComponent(const std::string& pMesh, std::weak_ptr<Texture> texture, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    SetTexture( "BaseColor", texture);
    mMaterial->SetVec2("uTiling", pTextureTiling);
}

MeshComponent::MeshComponent(std::weak_ptr<Mesh> pMesh, std::string& texture, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder), mMesh(pMesh)
{
    SetTexture("BaseColor", texture);
}

MeshComponent::MeshComponent(const std::string& pMesh, std::string& texture, Vector2 pTextureTiling, int pDrawOrder) : Component(pDrawOrder)
{
    mMesh = Assets::Get().GetMesh(pMesh);
    SetTexture("BaseColor", texture);
    mMaterial->SetVec2("uTiling", pTextureTiling);
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
        auto mat = mMaterial ? mMaterial.get() : temp->GetMaterial().get();

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
    if (!mMaterial.get())
    {
        std::string tempName = "MI_Mesh_" + Maths::Rand(0, 999);

        while (Assets::Get().GetMaterial(tempName).get())
        {
            tempName = "MI_Mesh_" + Maths::Rand(0, 999);
        }

        mMaterial = Assets::Get().CreateMaterialInstance(tempName, mMesh.lock()->GetMaterial());
    }
    mMaterial->SetTexture(textureName, texture);
    mMaterial->SetVec2("uTiling", tiling);
}    
     
void MeshComponent::SetTexture(std::string textureName, std::string& texture, Vector2 tiling)
{
    std::weak_ptr<Texture> tempTexture = Assets::Get().GetTexture(texture);

    if (!mMaterial)
    {
        std::string tempName = "MI_Mesh_" + Maths::Rand(0, 999);

        while (Assets::Get().GetMaterial(tempName).get())
        {
            tempName = "MI_Mesh_" + Maths::Rand(0, 999);
        }

        mMaterial = Assets::Get().CreateMaterialInstance(tempName, mMesh.lock().get()->GetMaterial());
    }

    mMaterial->SetTexture(textureName, tempTexture);
    mMaterial->SetVec2("uTiling", tiling);
}