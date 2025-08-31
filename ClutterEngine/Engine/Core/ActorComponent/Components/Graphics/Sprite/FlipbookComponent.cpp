#include "pch.h"
#include <Core/Timer.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/FlipbookComponent.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h> // Ensure SpriteComponent header is included

using namespace clt;

FlipbookComponent::FlipbookComponent(const std::vector< std::weak_ptr<Texture>>& pTexture, bool pLooping, int pDrawOrder) 
   : SpriteComponent(pTexture.empty() ? nullptr : pTexture[0].lock(), pDrawOrder), // Adjust constructor to handle weak_ptr
     mCurrentFrame(0.0f), 
     mAnimFps(10.0f), 
     mLooping(pLooping), 
     mIsPaused(false)
{
   SetFlipbookTextures(pTexture);
}

FlipbookComponent::~FlipbookComponent()
{
   mFlipbookTextures.clear();
}

void FlipbookComponent::SetFlipbookTextures(const std::vector<std::weak_ptr<Texture>> pTextures)
{
   mFlipbookTextures.clear();
   for (const auto& weakTexture : pTextures)
   {
       if (auto texture = weakTexture.lock())
       {
           mFlipbookTextures.push_back(texture);
       }
   }

   if (!mFlipbookTextures.empty() && mOwner)
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
       if (mFlipbookTextures.empty()) return;
       mCurrentFrame += mAnimFps * Timer::deltaTime;

       while (mCurrentFrame >= mFlipbookTextures.size())
       {
           mCurrentFrame -= mFlipbookTextures.size();
       }

       SetTexture(mFlipbookTextures[static_cast<int>(mCurrentFrame)]);
   }
}