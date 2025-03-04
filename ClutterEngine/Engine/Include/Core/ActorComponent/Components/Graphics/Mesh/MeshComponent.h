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

	public:

		MeshComponent(int pDrawOrder = 0);
		virtual ~MeshComponent() = default;

		virtual void SetOwner(Actor* pOwner) override;

		virtual void Draw(Matrix4Row viewProj);
		virtual void SetMesh(Mesh& pMesh) { mMesh = &pMesh; };
		void SetTextureIndex(size_t pTextureIndex);

	};
}