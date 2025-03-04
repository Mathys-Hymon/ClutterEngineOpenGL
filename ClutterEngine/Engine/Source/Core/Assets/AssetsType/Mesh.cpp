#include "pch.h"
#include <Core/Assets/AssetsType/Mesh.h>

using namespace clt;


Mesh::Mesh() : mShader(), mVAO()
{
	//mVAO = VertexArray(cubeVertices, 28, cubeIndices, 36);
}

void Mesh::Unload()
{
}
