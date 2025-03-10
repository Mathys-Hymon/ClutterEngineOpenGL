#include "pch.h"
#include <Core/Assets/AssetsType/Mesh.h>

using namespace clt;

const auto basicVertPah = "Content/Shaders/basic.vert";
const auto meshFragPath = "Content/Shaders/basic.frag";

Mesh::Mesh(const float* pVertices, u32 pVerticeCount)
{
    mShader = Shader();
    mShader.Load(basicVertPah, meshFragPath);

    mVAO = new VertexArray(pVertices, pVerticeCount);
}

void Mesh::Unload()
{
	delete mVAO;
	mVAO = nullptr;
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
