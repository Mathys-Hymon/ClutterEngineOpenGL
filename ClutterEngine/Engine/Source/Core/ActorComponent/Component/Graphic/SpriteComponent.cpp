#include "pch.h"
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>

using namespace clt;

SpriteComponent::SpriteComponent(Texture* pTexture, int DrawOrder) : GraphicComponent(DrawOrder), mTexture(pTexture), mTexHeight(pTexture->GetHeight()), mTexWidth(pTexture->GetWidth()), mFlipX(false), mFlipY(false)
    {}

SpriteComponent::~SpriteComponent() {}

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

    float xMultiplyer = mFlipX ? -100 : 100;
    float yMultiplyer = mFlipY ? -100 : 100;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(actorTransform.location.x + mRelativePosition.x, actorTransform.location.y + mRelativePosition.y, 0.0f));
    model = glm::rotate(model, glm::radians(actorTransform.rotation + mRelativeRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3((mRelativeScale.x* actorTransform.scale.x) * xMultiplyer, (mRelativeScale.y * actorTransform.scale.y) * yMultiplyer, 1.0f));

    return model;
}
