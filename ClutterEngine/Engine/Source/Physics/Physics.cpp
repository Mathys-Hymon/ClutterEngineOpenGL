#include "pch.h"
#include <Physics/Physics.h>

using namespace clt;

void Physics::AddCollider(Collider2DComponent* pCollider)
{

}

void Physics::RemoveCollider(Collider2DComponent* pCollider)
{
	std::map<Collider2DComponent*, CollisionEvent*>::iterator it;
	for (it = mColliderEvent.begin(); it != mColliderEvent.end(); it++)
	{
		delete it->second;
	}
	mColliderEvent.clear();
}

void Physics::SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener)
{
	size_t hasCollider = mColliderEvent.count(pCollider);

	if (!hasCollider)
	{
		mColliderEvent[pCollider] = new CollisionEvent();
	}
	mColliderEvent[pCollider]->Subscribe(pListener);
}

void Physics::Update()
{
	std::cout << mColliderEvent.size() << std::endl;
}
