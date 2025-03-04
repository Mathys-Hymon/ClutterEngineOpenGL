#include "pch.h"
#include <Core/Assets/AssetsType/Mesh.h>

using namespace clt;

constexpr float cubeVertices[] = {
    // Positions           // Coordonnées de texture
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face avant
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // Face arrière
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face gauche
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face droite
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // Face bas
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,   // Face haut
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f
};

constexpr unsigned int cubeIndices[] = {
   0, 2, 1,  1, 2, 3,  // Face avant
   4, 5, 6,  5, 7, 6,  // Face arrière
   8, 9, 10, 9, 11, 10, // Face gauche
   12, 13, 14, 13, 15, 14, // Face droite
   16, 17, 18, 17, 19, 18, // Face bas
   20, 21, 22, 21, 23, 22  // Face haut
};

const auto meshVertPath = "Content/Shaders/basic.vert";
const auto meshFragPath = "Content/Shaders/basic.frag";

Mesh::Mesh()
{
    mShader.Load(meshVertPath, meshFragPath);

    mVAO = new VertexArray(cubeVertices, 28, cubeIndices, 36);
}

Mesh::Mesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount)
{
    mShader = Shader();
    mShader.Load(meshVertPath, meshFragPath);

    mVAO = new VertexArray(pVertices, pVerticeCount, pIndices, pIndexCount);
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
	if (mVAO) mVAO->Set(pVertices, pIndexCount, pIndices, pIndexCount);
	else      mVAO = new VertexArray(pVertices, pIndexCount, pIndices, pIndexCount);
}
