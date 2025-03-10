#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Graphics/Shader/VertexArray.h>
#include <Graphics/Shader/Shader.h>

namespace clt
{
	class CLUTTER_API Mesh
	{
		std::vector<Texture*> mTextures;
		VertexArray* mVAO;

		Shader mShader;
	public:

		Mesh(const float* pVertices, u32 pVerticeCount);
		~Mesh() = default;

		void Unload();

		Texture* GetTexture(int pTextureIndex) { return mTextures[pTextureIndex]; }
		VertexArray& GetVAO() { return *mVAO; }
		Shader& GetShader() { return mShader; }

		void AddTexture(Texture* pTexture);
		void SetMesh(VertexArray* pVAO);
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}