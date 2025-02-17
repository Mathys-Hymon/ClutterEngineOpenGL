#pragma once
#include <Core/ActorComponent/Components/GraphicComponent.h>
#include <Core/Assets/AssetsType/Texture.h>

namespace clt
{
	class CLUTTER_API SpriteComponent : public GraphicComponent
	{
	protected:
		int mTexWidth, mTexHeight;
		Texture& mTexture;

	public:
		SpriteComponent(Actor* pOwner, Texture& pTexture, int DrawOrder = 0);
		SpriteComponent() = delete;
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent& operator = (const SpriteComponent&) = delete;

		virtual ~SpriteComponent();

		virtual void SetTexture(const Texture& pTexture);
		virtual void Draw(Renderer& pRenderer) override;

		int GetTexWidth() const { return mTexWidth; };
		int GetTexHeight() const { return mTexHeight; };
	};

}