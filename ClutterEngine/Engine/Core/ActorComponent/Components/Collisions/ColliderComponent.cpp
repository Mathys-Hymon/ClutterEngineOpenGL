#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>
#include <Physics/Physics.h>
#include <Core/Levels/Level.h>

using namespace clt;

void ColliderComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mOwner->GetLevel()->GetPhysics().AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	mOwner->GetLevel()->GetPhysics().RemoveCollider(this);
}
