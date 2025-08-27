#include "pch.h"
#include <Core/Assets/AssetsType/Mesh.h>
#include <Core/Assets/Assets.h>

using namespace clt;

const auto meshVertPathTes = "Content/Resources/Shaders/Mesh/basicTess.vert";
const auto meshFragPathTes = "Content/Resources/Shaders/Mesh/basicTess.frag";
const auto meshTescPath = "Content/Resources/Shaders/Mesh/basicTess.tesc";
const auto meshTesePath = "Content/Resources/Shaders/Mesh/basicTess.tese";

const auto meshFragPath = "Content/Resources/Shaders/basic.frag";
const auto meshVertPath = "Content/Resources/Shaders/basic.vert";

Mesh::Mesh(const float* pVertices, u32 pVerticeCount, bool tesselate)
{
    ShaderProgram* tempShader = new ShaderProgram();
    mTesselate = tesselate;

    if (tesselate)
    {
        tempShader->Compose({
            Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
            Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT),
            Assets::Get().LoadShader(meshTescPath, ShaderType::TESSELATION_CONTROL), 
            Assets::Get().LoadShader(meshTesePath, ShaderType::TESSELATION_EVALUATION) 
            });
    }
    else  tempShader->Compose({
        Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
        Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT), 
        });

    mMaterial = new Material(tempShader);
    mVAO = new VertexArray(pVertices, pVerticeCount);
}

Mesh::Mesh(const float* pVertices, u32 pVerticeCount, IMaterial* pMaterial, bool isTesselated)
  : mVertices()
{
   mMaterial = pMaterial;
   mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
   mTesselate = isTesselated;
}

Mesh::Mesh(std::vector<Vertex> pVertices, IMaterial* pMaterial, bool isTesselated)
    : mVertices(std::move(pVertices))
{
    mMaterial = pMaterial;
    mTesselate = isTesselated;

    mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
}

Mesh::Mesh(std::vector<Vertex> pVertices, bool tesselate) 
    : mVertices(std::move(pVertices))
{
    ShaderProgram* tempShader = new ShaderProgram();
    mTesselate = tesselate;

    if (tesselate)
    {
        tempShader->Compose({
            Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
            Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT),
            Assets::Get().LoadShader(meshTescPath, ShaderType::TESSELATION_CONTROL),
            Assets::Get().LoadShader(meshTesePath, ShaderType::TESSELATION_EVALUATION) });
    }
    else
    {
        tempShader->Compose({
        Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
        Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT) 
            });
    }

    mMaterial = new Material(tempShader);
	mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
}

void Mesh::Unload()
{
	delete mVAO;
	mVAO = nullptr;
}

Texture* Mesh::GetTexture(std::string& const pTextureName)
{
    return mMaterial->GetTexture(pTextureName);
}

float* Mesh::ToVerticeArray()
{
    float* array = new float[mVertices.size() * 8];
    int counter = 0;
    for (int i = 0; i < mVertices.size(); i++)
    {
        array[counter]     = mVertices[i].position.x;
        array[counter + 1] = mVertices[i].position.y;
        array[counter + 2] = mVertices[i].position.z;
        array[counter + 3] = mVertices[i].normal.x;
        array[counter + 4] = mVertices[i].normal.y;
        array[counter + 5] = mVertices[i].normal.z;
        array[counter + 6] = mVertices[i].texCoord.x;
        array[counter + 7] = mVertices[i].texCoord.y;
        counter += 8;
    }
    return array;

}

void Mesh::AddTexture(std::string pName, Texture* pTexture)
{
    mMaterial->SetTexture(pName, pTexture);
}

void Mesh::SetTexture(std::string& textureName, Texture* texture)
{    
    mMaterial->SetTexture(textureName, texture);
}    
     
void Mesh::SetTexture(std::string& textureName, std::string& texture)
{
    Texture* tempTexture = Assets::Get().GetTexture(texture);

    mMaterial->SetTexture(textureName, tempTexture);
}

void Mesh::SetMesh(VertexArray* pVAO)
{
	if (mVAO) delete mVAO;

	mVAO = pVAO;
}

void Mesh::SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount)
{
	if (mVAO) mVAO->Set(pVertices, pVerticeCount);
	else      mVAO = new VertexArray(pVertices, pVerticeCount);
}
