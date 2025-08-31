#include "pch.h"
#include <Core/Timer.h>
#include "FlipbookElement.h"

using namespace clt;

void FlipbookElement::SetFlipbookTextures(const std::vector<std::weak_ptr<Texture>>& pTextures)
{
	mFlipbookTextures = pTextures;
	if (mFlipbookTextures.size() > 0)
	{
		SetTexture(mFlipbookTextures[0]);
	}
	mCurrentFrame = 0.0f;
	mNextFrame = mCurrentFrame + 1.0f;
}

void FlipbookElement::Update()
{
	SpriteElement::Update();

	if (((!mLooping && mCurrentFrame < mFlipbookTextures.size() - 1) || (mLooping)) && (!mIsPaused))
	{
		if (mFlipbookTextures.size() == 0) return;
		mCurrentFrame += mAnimFps * Timer::deltaTime;

		while (mCurrentFrame >= mFlipbookTextures.size())
		{
			mCurrentFrame -= mFlipbookTextures.size();
			mNextFrame = mCurrentFrame + 1.0f;
		}

		if (mCurrentFrame > mNextFrame)
		{
			SetTexture(mFlipbookTextures[static_cast<int>(mCurrentFrame)]);
			mNextFrame = mCurrentFrame + 1.0f;
		}

	}
}
