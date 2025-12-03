#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>

using namespace clt;

REGISTER_COMPONENT_CLASS(SpriteComponent);

SpriteComponent::SpriteComponent(std::weak_ptr<Texture> pTexture, int DrawOrder) 
    : Component(DrawOrder), 
      mTexture(pTexture), 
      mTexHeight(0), 
      mTexWidth(0), 
      mFlipX(false), 
      mFlipY(false)
{
    if (auto texture = mTexture.lock())
    {
        mTexHeight = texture->GetHeight();
        mTexWidth = texture->GetWidth();
    }
}

void SpriteComponent::SetOwner(Actor* pOwner)
{
    Component::SetOwner(pOwner);
    mOwner->GetLevel()->GetRenderer().AddSpriteComponent(this);
}

void SpriteComponent::SetTexture(std::weak_ptr<Texture> pTexture)
{
    mTexture = pTexture;
    if (auto texture = mTexture.lock())      texture->UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::SetTexture(const std::string& pTexture)
{
    mTexture = Assets::Get().GetTexture(pTexture);
    if (auto texture = mTexture.lock())      texture->UpdateInfo(mTexWidth, mTexHeight);
}