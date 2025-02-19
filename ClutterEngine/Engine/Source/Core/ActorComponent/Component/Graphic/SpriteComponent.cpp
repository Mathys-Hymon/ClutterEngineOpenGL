#include "pch.h"
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>

using namespace clt;

SpriteComponent::SpriteComponent(Texture* pTexture, int DrawOrder) : GraphicComponent(DrawOrder), mTexture(pTexture), mTexHeight(pTexture->GetHeight()), mTexWidth(pTexture->GetWidth())
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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(actorTransform.location.x + mRelativePosition.x, actorTransform.location.y + mRelativePosition.y, 0.0f));
    model = glm::rotate(model, glm::radians(actorTransform.rotation + mRelativeRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3((mRelativeScale.x* actorTransform.scale.x) * 100, (mRelativeScale.y * actorTransform.scale.y) * 100, 1.0f));

    return model;
}
