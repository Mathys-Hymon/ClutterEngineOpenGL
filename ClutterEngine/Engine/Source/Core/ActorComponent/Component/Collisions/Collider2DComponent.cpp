#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>
#include <Physics/Physics.h>
#include <Core/Levels/Level.h>

using namespace clt;

Collider2DComponent::Collider2DComponent() : mFriction(2.5f), mBounciness(0.3f)
{
}

void Collider2DComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mOwner->GetLevel()->GetPhysics().AddCollider(this);
}