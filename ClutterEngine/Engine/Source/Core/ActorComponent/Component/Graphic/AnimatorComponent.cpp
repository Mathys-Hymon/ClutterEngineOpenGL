#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/AnimatorComponent.h>

using namespace clt;

AnimatorComponent::AnimatorComponent(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping, int pDrawOrder)
	: FlipbookComponent(pTextures, pLooping, pDrawOrder)
{
	mAnims[pAnimName] = new FlipbookComponent(pTextures, pLooping, pDrawOrder);
}

void AnimatorComponent::AddNewAnim(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping, int pDrawOrder)
{
	if (mAnims[pAnimName]) CLUTTER_WARNING(("Animation " + pAnimName + " already exists ").c_str())
	else mAnims[pAnimName] = new FlipbookComponent(pTextures, pLooping, pDrawOrder);
}

void AnimatorComponent::PlayAnim(std::string pAnimName)
{
	if (!mAnims[pAnimName]) CLUTTER_WARNING(("Unable to play " + pAnimName + " animation, animation not loaded or does not exist").c_str())
	else
	{
		SetFlipbookTextures(mAnims[pAnimName]->GetFlipbookTextures());
		SetFlipbookFps(mAnims[pAnimName]->GetFlipbookFps());
		SetLooping(mAnims[pAnimName]->GetLooping());
	}
}

void AnimatorComponent::RemoveAnim(std::string pAnimName)
{
	
}
