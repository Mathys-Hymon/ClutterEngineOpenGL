#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Graphics/Shader/VertexArray.h>
#include <Graphics/Shader/Shader.h>

namespace clt
{
	struct CLUTTER_API Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoord;
	};

	class CLUTTER_API Mesh
	{
		std::vector<Texture*> mTextures;
		Vector2 mTextureTiling = { 1,1 };

		VertexArray* mVAO;

		std::vector<Vertex> mVertices;

		Shader mShader;

		float* ToVerticeArray();

	public:

		Mesh() {};
		Mesh(const float* pVertices, u32 pVerticeCount);
		Mesh(std::vector<Vertex> pVertices);
		~Mesh() = default;

		void Unload();

		Texture* GetTexture(int pTextureIndex) 
		{ 
			if (mTextures.empty() || mTextures.size() < pTextureIndex) return nullptr;
			return mTextures[pTextureIndex]; 
		
		}
		VertexArray& GetVAO() { return *mVAO; }
		Shader& GetShader() { return mShader; }

		void AddTexture(Texture* pTexture);

		void SetTexture(Texture* texture,size_t index);
		void SetTexture(std::string& texture, size_t index);

		void SetTextureTiling(Vector2 tiling) { mTextureTiling = tiling; };
		Vector2 GetTextureTiling() const { return mTextureTiling; };

		void SetMesh(VertexArray* pVAO);
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}