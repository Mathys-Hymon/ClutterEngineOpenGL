#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Graphics/RendererGL.h>
#include <Core/Levels/Level.h>

namespace clt
{
	class CLUTTER_API SpriteComponent : public Component
	{
	protected:
		int mTexWidth, mTexHeight;
		bool mFlipX, mFlipY;
		std::weak_ptr<Texture> mTexture;

	public:
		CLUTTER_CLASS(SpriteComponent);
		
		void SetupProperties() override 
		{
			CPROPERTY(mTexWidth, clt::PropMode::ReadWrite);
			CPROPERTY(mTexHeight, clt::PropMode::ReadWrite);
			CPROPERTY(mFlipX, clt::PropMode::ReadWrite);
			CPROPERTY(mFlipY, clt::PropMode::ReadWrite);
			CPROPERTY(mTexture, clt::PropMode::ReadWrite);
		}
		
		SpriteComponent(std::weak_ptr<Texture> pTexture, int DrawOrder = 0);
		SpriteComponent(int DrawOrder = 0) : Component(DrawOrder) {};
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent& operator = (const SpriteComponent&) = delete;

		virtual ~SpriteComponent() { if(mOwner) mOwner->GetLevel()->GetRenderer().RemoveSpriteComponent(this); };

		virtual void SetOwner(Actor* pOwner) override;

		virtual void SetTexture(std::weak_ptr<Texture> pTexture);
		virtual void SetTexture(const std::string& pTexture);

		void SetFlipX(bool pFlip)  { mFlipX = pFlip;  };
		void SetFlipY(bool pFlipY) { mFlipY = pFlipY; };

		bool GetFlipX() const { return mFlipX; };
		bool GetFlipY() const { return mFlipY; };


		int GetTexWidth() const { return mTexWidth; };
		int GetTexHeight() const { return mTexHeight; };
		std::weak_ptr<Texture> GetTexture() const { return mTexture; };
	};

}