#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Assets/AssetsType/Mesh.h>

namespace clt
{
	class CLUTTER_API MeshComponent : public Component
	{
	protected:
		std::weak_ptr<Mesh> mMesh;
		std::weak_ptr<IMaterial> mMaterial;

		bool mTesselate;

	public:

		MeshComponent(std::weak_ptr<Mesh> pMesh, int pDrawOrder = 0, Vector2 pTextureTiling = {5,5});
		MeshComponent(const std::string& pMesh, int pDrawOrder = 0, Vector2 pTextureTiling = { 5,5 });


		MeshComponent(std::weak_ptr<Mesh> pMesh,std::weak_ptr<IMaterial>, Vector2 pTextureTiling = { 5,5 }, int pDrawOrder = 0);
		MeshComponent(const std::string& pMesh, std::weak_ptr<IMaterial>, Vector2 pTextureTiling = { 5,5 }, int pDrawOrder = 0);

		virtual ~MeshComponent();

		virtual void SetOwner(Actor* pOwner) override;

		virtual void Draw(Matrix4Row viewProj);
		virtual void SetMesh(std::weak_ptr<Mesh> pMesh) { mMesh = pMesh; };
		Mesh& GetMesh() const { return *mMesh.lock().get(); };

		void SetTexture(std::string textureName, std::weak_ptr<Texture> texture, Vector2 tiling = { 5,5 });
		void SetTexture(std::string textureName, std::string& texture, Vector2 tiling = { 5,5 });

	};
}