#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/VertexArray.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Core/Assets/AssetsType/Material.h>

namespace clt
{
	class Assets;
	struct CLUTTER_API Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoord;
	};

	class CLUTTER_API Mesh
	{
		Material* mMaterial;

		std::vector<Texture*> mTextures;
		Vector2 mTextureTiling = { 1,1 };

		VertexArray* mVAO;

		std::vector<Vertex> mVertices;

		bool mTesselate;

		float* ToVerticeArray();

	public:

		Mesh() {};
		Mesh(const float* pVertices, u32 pVerticeCount, bool tesselate);
		Mesh(const float* pVertices, u32 pVerticeCount, Material* pMaterial, bool isTesselated);
		Mesh(std::vector<Vertex> pVertices, Material* pMaterial, bool isTesselated);
		Mesh(std::vector<Vertex> pVertices, bool tesselate);
		~Mesh() = default;

		void Unload();

		Texture* GetTexture(int pTextureIndex);

		bool HasTexture(Texture* pTextureIndex)
		{
			mMaterial->HasTexture(pTextureIndex);
		}

		VertexArray& GetVAO() { return *mVAO; }
		Material& GetMaterial() { return *mMaterial; }

		void AddTexture(Texture* pTexture);

		void SetTexture(Texture* texture,size_t& index);
		void SetTexture(std::string& texture, size_t& index);

		void SetTextureTiling(Vector2 tiling) { mTextureTiling = tiling; };
		Vector2 GetTextureTiling() const { return mTextureTiling; };

		bool GetTesselated() const { return mTesselate; };

		void SetMesh(VertexArray* pVAO);
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}