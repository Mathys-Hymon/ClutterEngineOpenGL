#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Assets/AssetsType/Mesh.h>

namespace clt
{
	class CLUTTER_API MeshComponent : public Component
	{
	protected:
		Mesh* mMesh;
		size_t mTextureIndex;

		bool mTesselate;

	public:

		MeshComponent(Mesh* pMesh, int pDrawOrder = 0, Vector2 pTextureTiling = {1,1});
		virtual ~MeshComponent() = default;

		virtual void SetOwner(Actor* pOwner) override;

		virtual void Draw(Matrix4Row viewProj);
		virtual void SetMesh(Mesh& pMesh) { mMesh = &pMesh; };
		Mesh* GetMesh() const { return mMesh; };

		void SetTexture(Texture* texture, size_t index = 0);
		void SetTexture(std::string& texture, size_t index = 0);
		void SetTextureIndex(size_t pTextureIndex);

	};
}