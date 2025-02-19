#include "pch.h"
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>

using namespace clt;

SpriteComponent::SpriteComponent(Texture& pTexture, int DrawOrder) : GraphicComponent(DrawOrder), mTexture(pTexture), mTexHeight(pTexture.GetHeight()), mTexWidth(pTexture.GetWidth())
{

}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
	mTexture = pTexture;
	mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(Renderer& pRenderer)
{
	Vector2 origin{ mTexWidth / 2.0f, mTexHeight / 2.0f };
	pRenderer.DrawSprite(*mOwner, mTexture, CRectangle(), origin);
}
