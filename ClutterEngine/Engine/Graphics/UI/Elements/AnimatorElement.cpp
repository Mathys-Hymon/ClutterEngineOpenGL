#include "pch.h"
#include "AnimatorElement.h"

using namespace clt;

AnimatorElement::AnimatorElement(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping, float pAnimFps, Vector2 pSize, Vector2 pPosition, int zOrder) : FlipbookElement(pTextures, pLooping, pAnimFps, pSize, pPosition, zOrder)
{
	mAnims[pAnimName] = new FlipbookElement(pTextures, pLooping, pAnimFps);
}

AnimatorElement::~AnimatorElement()
{
	for (auto& anim : mAnims)
	{
		if (anim.second)
		{
			delete anim.second;
		}
	}
	mAnims.clear();
}

void AnimatorElement::AddNewAnim(std::string pAnimName, const std::vector<Texture*>& pTextures, bool pLooping, float pAnimFps, int pDrawOrder)
{
	if (mAnims[pAnimName]) CLUTTER_WARNING(("Animation " + pAnimName + " already exists ").c_str())
	else mAnims[pAnimName] = new FlipbookElement(pTextures, pLooping, pAnimFps);
}

void AnimatorElement::PlayAnim(std::string pAnimName)
{
	if (!mAnims[pAnimName]) CLUTTER_WARNING(("Unable to play " + pAnimName + " animation, animation not loaded or does not exist").c_str())
	else
	{
		SetFlipbookTextures(mAnims[pAnimName]->GetFlipbookTextures());
		SetFlipbookFps(mAnims[pAnimName]->GetFlipbookFps());
		SetLooping(mAnims[pAnimName]->GetLooping());
	}
}

void AnimatorElement::RemoveAnim(std::string pAnimName)  
{  
   auto it = mAnims.find(pAnimName);  
   if (it != mAnims.end())  
   {  
       delete it->second;
       mAnims.erase(it);
   }  
   else  
   {  
       CLUTTER_WARNING(("Animation " + pAnimName + " does not exist").c_str());  
   }  
}
