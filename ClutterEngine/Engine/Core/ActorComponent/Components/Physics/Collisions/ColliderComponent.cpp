#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Collisions/ColliderComponent.h>
#include <Physics/Collision/ICollisionListener.h>
#include <Physics/IPhysics.h>
#include <Core/Levels/Level.h>

using namespace clt;

void ColliderComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	//mOwner->GetLevel()->GetPhysics().AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	//mOwner->GetLevel()->GetPhysics().RemoveCollider(this);
}

void ColliderComponent::Subscribe(ICollisionListener* listener) const
{
	//mOwner->GetLevel()->GetPhysics().SubscribeTo(const_cast<ColliderComponent*>(this), listener); 
}
