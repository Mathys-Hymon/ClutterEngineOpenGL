#pragma once
#include <Core/CCommon.h>
#include <vector>
#include <Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>

namespace clt
{
	class CLUTTER_API FlipbookComponent : public SpriteComponent
	{
		std::vector< std::weak_ptr<Texture>> mFlipbookTextures;
		bool mLooping, mIsPaused;
		float mCurrentFrame;
		float mAnimFps;

	public:
		
		CLUTTER_CLASS(FlipbookComponent);
		
		void SetupProperties() override 
		{
			CPROPERTY(mLooping, clt::PropMode::ReadWrite);
			CPROPERTY(mIsPaused, clt::PropMode::ReadWrite);
			CPROPERTY(mCurrentFrame, clt::PropMode::ReadOnly);
			CPROPERTY(mAnimFps, clt::PropMode::ReadWrite);
			CPROPERTY(mFlipbookTextures, clt::PropMode::ReadWrite);
		}
		
		FlipbookComponent(const std::vector<std::weak_ptr<Texture>>& pTexture, bool pLooping = true, int pDrawOrder = 100);
		FlipbookComponent() : SpriteComponent() {};
		FlipbookComponent(const FlipbookComponent&) = delete;
		FlipbookComponent& operator = (const FlipbookComponent&) = delete;

		virtual ~FlipbookComponent();
		
		virtual void SetOwner(Actor* pOwner) override 
		{ 
			SpriteComponent::SetOwner(pOwner);
			SetTexture(mFlipbookTextures[0]);
		}

		float GetFlipbookFps() const { return mAnimFps; }

		void SetFlipbookTextures(const std::vector< std::weak_ptr<Texture>> pTextures);
		void SetFlipbookFps(float pFps);
		void SetLooping(bool pLooping) { mLooping = pLooping; };

		std::vector<std::weak_ptr<Texture>> GetFlipbookTextures() const { return mFlipbookTextures; };
		bool GetLooping() const { return mLooping; };

		void Play()   { mIsPaused = false; };
		void Pause()  { mIsPaused = true; };
		void Toggle() { mIsPaused = !mIsPaused; };
		void Update() override;
	};
}
