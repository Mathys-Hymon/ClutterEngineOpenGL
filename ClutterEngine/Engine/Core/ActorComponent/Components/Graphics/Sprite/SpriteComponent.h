#pragma once
#include <Core/ActorComponent/Component.h>
#include <Graphics/RendererGL.h>
#include <Core/Levels/Level.h>
#include <Core/Assets/AssetsType/Texture.h>

namespace clt
{
	class CLUTTER_API SpriteComponent : public Component
	{
	protected:
		int mTexWidth, mTexHeight;
		bool mFlipX, mFlipY;
		Texture* mTexture;

	public:
		SpriteComponent(Texture* pTexture, int DrawOrder = 0);
		SpriteComponent() = delete;
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent& operator = (const SpriteComponent&) = delete;

		virtual ~SpriteComponent();

		virtual void SetOwner(Actor* pOwner) override;

		virtual void Unload() override
		{
			mOwner->GetLevel()->GetRenderer().RemoveSpriteComponent(this);
		};

		virtual void SetTexture(Texture* pTexture);

		void SetFlipX(bool pFlip)  { mFlipX = pFlip;  };
		void SetFlipY(bool pFlipY) { mFlipY = pFlipY; };

		int GetTexWidth() const { return mTexWidth; };
		int GetTexHeight() const { return mTexHeight; };
		Texture* GetTexture() const { return mTexture; };
	};

}