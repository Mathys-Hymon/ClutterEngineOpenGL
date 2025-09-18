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
		std::shared_ptr<IMaterial> mMaterial;

		VertexArray* mVAO;

		std::vector<Vertex> mVertices;

		bool mTesselate;

		float* ToVerticeArray();

	public:

		Mesh() = default;
		Mesh(const float* pVertices, u32 pVerticeCount, bool tesselate);
		Mesh(const float* pVertices, u32 pVerticeCount, std::shared_ptr<IMaterial> pMaterial, bool isTesselated);
		Mesh(std::vector<Vertex> pVertices, std::shared_ptr<IMaterial> pMaterial, bool isTesselated);
		Mesh(std::vector<Vertex> pVertices, bool tesselate);
		~Mesh() = default;

		void Unload();

		std::weak_ptr<Texture> GetTexture(std::string& const pTextureName);

		bool HasTexture(std::weak_ptr<Texture> pTexture)
		{
			return mMaterial->HasTexture(pTexture);
		}

		VertexArray& GetVAO() { return *mVAO; }
		IMaterial& GetMaterialRef() { return *mMaterial.get(); }
		std::shared_ptr<IMaterial> GetMaterial() { return mMaterial; }

		void AddTexture(std::string name, std::weak_ptr<Texture> pTexture);

		void SetTexture(std::string& textureName, std::weak_ptr<Texture> texture);
		void SetTexture(std::string& textureName, std::string& texture);

		void SetTextureTiling(Vector2 tiling) { mMaterial.get()->SetVec2("uTiling", tiling); };
		Vector2 GetTextureTiling() const { return mMaterial.get()->GetVec2("uTiling"); };

		bool GetTesselated() const { return mTesselate; };

		void SetMesh(VertexArray* pVAO);
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}