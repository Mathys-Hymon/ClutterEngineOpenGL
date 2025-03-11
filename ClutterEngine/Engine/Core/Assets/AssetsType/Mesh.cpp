#include "pch.h"
#include <Core/Assets/AssetsType/Mesh.h>

using namespace clt;

const auto basicVertPah = "Content/Resources/Shaders/basic.vert";
const auto meshFragPath = "Content/Resources/Shaders/basic.frag";

Mesh::Mesh(const float* pVertices, u32 pVerticeCount)
{
    mShader = Shader();
    mShader.Load(basicVertPah, meshFragPath);

    mVAO = new VertexArray(pVertices, pVerticeCount);
}

Mesh::Mesh(std::vector<Vertex> pVertices) : mVertices(std::move(pVertices))
{
	mShader = Shader();
	mShader.Load(basicVertPah, meshFragPath);

	mVAO = new VertexArray(ToVerticeArray(), mVertices.size());
}

void Mesh::Unload()
{
	delete mVAO;
	mVAO = nullptr;
}

float* Mesh::ToVerticeArray()
{
    float* array = new float[mVertices.size() * 8];
    int counter = 0;
    for (int i = 0; i < mVertices.size(); i++)
    {
        array[counter + 0] = mVertices[i].position.x;
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
