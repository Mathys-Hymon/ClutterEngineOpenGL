#pragma once
#include <Graphics/UI/Elements/SpriteElement.h>

namespace clt
{
	class CLUTTER_API FlipbookElement : public SpriteElement
	{
		std::vector<Texture*> mFlipbookTextures;
		bool mLooping, mIsPaused;
		float mCurrentFrame, mNextFrame;
		float mAnimFps;

	public:
		FlipbookElement() = delete;

		FlipbookElement(const std::vector<Texture*> pTexture, bool pLooping = true, float pAnimFps = 24, Vector2 size = { 1.0f ,1.0f }, Vector2 position = { 0, 0 }, int ZOrder = 0) : SpriteElement(pTexture[0],size, position, ZOrder), mFlipbookTextures(pTexture), mLooping(pLooping), mIsPaused(false), mAnimFps(pAnimFps), mCurrentFrame(0), mNextFrame(1)
		{};

		std::vector<Texture*> GetFlipbookTextures() const { return mFlipbookTextures; };
		bool GetLooping() const { return mLooping; };

		void SetFlipbookTextures(const std::vector<Texture*> pTextures);
		void SetFlipbookFps(float pFps) { mAnimFps = pFps; };
		void SetLooping(bool pLooping) { mLooping = pLooping; };

		void Play() { mIsPaused = false; };
		void Pause() { mIsPaused = true; };
		void Toggle() { mIsPaused = !mIsPaused; };

		virtual void Update() override;
	};
}