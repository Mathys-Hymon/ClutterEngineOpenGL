#pragma once
#include <Core/CCommon.h>
#include <vector>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>

namespace clt
{
	class CLUTTER_API FlipbookComponent : public SpriteComponent
	{
		std::vector<Texture*> mFlipbookTextures;
		bool mLooping, mIsPaused;
		float mCurrentFrame;
		float mAnimFps;

	public:
		FlipbookComponent(const std::vector<Texture*>& pTexture, bool pLooping = true, int pDrawOrder = 100);
		FlipbookComponent() = delete;
		FlipbookComponent(const FlipbookComponent&) = delete;
		FlipbookComponent& operator = (const FlipbookComponent&) = delete;

		virtual ~FlipbookComponent();

		virtual void SetOwner(Actor* pOwner) override
		{
			mOwner = pOwner;
			SetTexture(mFlipbookTextures[0]);
		};

		float GetFlipbookFps() const { return mAnimFps; }

		void SetFlipbookTextures(const std::vector<Texture*> pTextures);
		void SetFlipbookFps(float pFps);
		void SetLooping(bool pLooping) { mLooping = pLooping; };

		void Play()   { mIsPaused = false; };
		void Pause()  { mIsPaused = true; };
		void Toggle() { mIsPaused = !mIsPaused; };
		void Update() override;
	};
}
