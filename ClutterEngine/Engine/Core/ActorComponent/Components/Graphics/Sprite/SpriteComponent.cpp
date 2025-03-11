#include "pch.h"
#include<Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>

using namespace clt;

SpriteComponent::SpriteComponent(Texture* pTexture, int DrawOrder) : Component(DrawOrder), mTexture(pTexture), mTexHeight(pTexture->GetHeight()), mTexWidth(pTexture->GetWidth()), mFlipX(false), mFlipY(false)
    {}

void SpriteComponent::SetOwner(Actor* pOwner)
{
    Component::SetOwner(pOwner);
    mOwner->GetLevel()->GetRenderer().AddSpriteComponent(this);
}

void SpriteComponent::SetTexture(Texture* pTexture)
{
    mOwner->GetLevel()->GetRenderer().RemoveSpriteComponent(this);
	mTexture = pTexture;
	mTexture->UpdateInfo(mTexWidth, mTexHeight);

    mOwner->GetLevel()->GetRenderer().AddSpriteComponent(this);
}
 