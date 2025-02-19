#include "pch.h"
#include <Core/Timer.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>

using namespace clt;

FlipbookComponent::FlipbookComponent(const std::vector<Texture*>& pTexture, bool pLooping, int pDrawOrder) : SpriteComponent(pTexture[0], pDrawOrder), mCurrentFrame(0.0f), mAnimFps(10.0f), mLooping(pLooping), mIsPaused(false)
{
	SetFlipbookTextures(pTexture);
}

FlipbookComponent::~FlipbookComponent()
{
	for (Texture* t : mFlipbookTextures)
	{
		t->~Texture();
	}
	mFlipbookTextures.clear();
}

void FlipbookComponent::SetFlipbookTextures(const std::vector<Texture*> pTextures)
{
	mFlipbookTextures = pTextures;
	if (mFlipbookTextures.size() > 0 && mOwner)
	{
		SetTexture(mFlipbookTextures[0]);
	}
}

void FlipbookComponent::SetFlipbookFps(float pFps)
{
	mAnimFps = pFps;
}
void FlipbookComponent::Update()
{
	SpriteComponent::Update();

	if (((!mLooping && mCurrentFrame < mFlipbookTextures.size() - 1) || (mLooping)) && (!mIsPaused))
	{
		if (mFlipbookTextures.size() == 0) return;
		mCurrentFrame += mAnimFps * Timer::deltaTime;

		while (mCurrentFrame >= mFlipbookTextures.size())
		{
			mCurrentFrame -= mFlipbookTextures.size();
		}

		SetTexture(mFlipbookTextures[static_cast<int>(mCurrentFrame)]);
	}

}