#include "pch.h"
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>

using namespace clt;

SpriteComponent::SpriteComponent(Texture* pTexture, int DrawOrder) : GraphicComponent(DrawOrder), mTexture(pTexture), mTexHeight(pTexture->GetHeight()), mTexWidth(pTexture->GetWidth()), mFlipX(false), mFlipY(false)
    {}

SpriteComponent::~SpriteComponent() {}

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

glm::mat4 SpriteComponent::GetTransform() const
{
    Transform2D actorTransform = mOwner->getTransform();

    float xMultiplyer = mFlipX ? -mTexHeight : mTexHeight;
    float yMultiplyer = mFlipY ? -mTexWidth : mTexWidth;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(actorTransform.location.x + mRelativeTransform.location.x, actorTransform.location.y + mRelativeTransform.location.y, 0.0f));
    model = glm::rotate(model, glm::radians(actorTransform.rotation + mRelativeTransform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3((mRelativeTransform.scale.x* actorTransform.scale.x) * xMultiplyer, (mRelativeTransform.scale.y * actorTransform.scale.y) * yMultiplyer, 1.0f));

    return model;
}
