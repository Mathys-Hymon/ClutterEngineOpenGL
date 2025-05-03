#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Assets/AssetsType/Mesh.h>

namespace clt
{
	class CLUTTER_API MeshComponent : public Component
	{
	protected:
		Mesh* mMesh;

		Texture* mTexture;
		Vector2 mTextureTiling;

		bool mTesselate;

	public:

		MeshComponent(Mesh* pMesh, int pDrawOrder = 0, Vector2 pTextureTiling = {5,5});
		MeshComponent(const std::string& pMesh, int pDrawOrder = 0, Vector2 pTextureTiling = { 5,5 });
		virtual ~MeshComponent();

		virtual void SetOwner(Actor* pOwner) override;

		virtual void Draw(Matrix4Row viewProj);
		virtual void SetMesh(Mesh& pMesh) { mMesh = &pMesh; };
		Mesh* GetMesh() const { return mMesh; };

		void SetTexture(Texture* texture, Vector2 tiling = {5,5});
		void SetTexture(std::string& texture, Vector2 tiling = { 5,5 });

	};
}