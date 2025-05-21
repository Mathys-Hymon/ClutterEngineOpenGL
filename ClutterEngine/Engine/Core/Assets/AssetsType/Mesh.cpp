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
    mShader = new ShaderProgram();
    mTesselate = tesselate;

    if (tesselate)
    {
        mShader->Compose({
            Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
            Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT),
            Assets::Get().LoadShader(meshTescPath, ShaderType::TESSELATION_CONTROL), 
            Assets::Get().LoadShader(meshTesePath, ShaderType::TESSELATION_EVALUATION) });
    }
    else  mShader->Compose({ 
        Assets::Get().LoadShader(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX),
        Assets::Get().LoadShader(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT), 
        });



    mVAO = new VertexArray(pVertices, pVerticeCount);
}

Mesh::Mesh(const float* pVertices, u32 pVerticeCount, ShaderProgram* pShader, bool isTesselated)
  : mVertices()
{
   mShader = pShader;
   mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
   mTesselate = isTesselated;
}

Mesh::Mesh(std::vector<Vertex> pVertices, ShaderProgram* pShader, bool isTesselated) : mVertices(std::move(pVertices))
{
    mShader = pShader;
    mTesselate = isTesselated;

    mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
}

Mesh::Mesh(std::vector<Vertex> pVertices, bool tesselate) : mVertices(std::move(pVertices))
{
    mShader = new ShaderProgram();
    mTesselate = tesselate;

    Shader* vert = new Shader();
    vert->Load(tesselate ? meshVertPathTes : meshVertPath, ShaderType::VERTEX);

    Shader* frag = new Shader();
    frag->Load(tesselate ? meshFragPathTes : meshFragPath, ShaderType::FRAGMENT);

    if (tesselate)
    {
        Shader* tesc = new Shader();
        tesc->Load(meshTescPath, ShaderType::TESSELATION_CONTROL);
        Shader* tese = new Shader();
        tese->Load(meshTesePath, ShaderType::TESSELATION_EVALUATION);

        mShader->Compose({ frag, vert , tesc, tese });
    }
    else  mShader->Compose({ frag, vert });

	mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
}

void Mesh::Unload()
{
	delete mVAO;
	mVAO = nullptr;
}

Texture* Mesh::GetTexture(int pTextureIndex)
{
    if (mTextures.empty()) return Assets::Get().GetTexture("default");
    else if (mTextures.size() <= pTextureIndex) return mTextures[0];

    return mTextures[pTextureIndex];
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

void Mesh::AddTexture(Texture* pTexture)
{
    mTextures.push_back(pTexture);
}

void Mesh::SetTexture(Texture* texture, size_t& index)
{    
    if (index >= mTextures.size())
    {
        mTextures.emplace_back(texture);
        index = mTextures.size() - 1;
    }
    else
    {
        mTextures[index] = texture;
    }
}    
     
void Mesh::SetTexture(std::string& texture, size_t& index)
{
    Texture* tempTexture = Assets::Get().GetTexture(texture);

    if (mTextures.size() <= index)
    {
        mTextures.emplace_back(tempTexture);
        index = mTextures.size() - 1;
    }
    else
    {
        mTextures[index] = tempTexture;
    }
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
