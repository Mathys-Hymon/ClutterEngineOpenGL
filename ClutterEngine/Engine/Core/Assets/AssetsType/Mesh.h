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

		Texture* GetTexture(std::string& const pTextureName);

		bool HasTexture(Texture* pTexture)
		{
			return mMaterial->HasTexture(pTexture);
		}

		VertexArray& GetVAO() { return *mVAO; }
		Material& GetMaterial() { return *mMaterial; }

		void AddTexture(std::string name, Texture* pTexture);

		void SetTexture(std::string& textureName, Texture* texture);
		void SetTexture(std::string& textureName, std::string& texture);

		void SetTextureTiling(Vector2 tiling) { mTextureTiling = tiling; };
		Vector2 GetTextureTiling() const { return mTextureTiling; };

		bool GetTesselated() const { return mTesselate; };

		void SetMesh(VertexArray* pVAO);
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}