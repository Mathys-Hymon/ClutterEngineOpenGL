#include "pch.h"
#include <Physics/Collision/CollisionEvent.h>

using namespace clt;

CollisionEvent::~CollisionEvent()
{
	mListeners.clear();
}

void CollisionEvent::Subscribe(ICollisionListener* pListener)
{
	mListeners.push_back(pListener);
}

void CollisionEvent::UnSubscribe(ICollisionListener* pListener)
{
	std::vector<ICollisionListener*>::iterator it;

	if ((it = std::find(mListeners.begin(), mListeners.end(), pListener)) != mListeners.end())
	{
		mListeners.erase(it); 
	}
}

void CollisionEvent::NotifyEnter(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnCollisionEnter(collider, result);
	}	
}

void CollisionEvent::NotifyStay(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnCollisionStay(collider, result);
	}
}

void CollisionEvent::NotifyExit(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnCollisionExit(collider,result);
	}
}

void CollisionEvent::TriggerEnter(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnTriggerEnter(collider, result);
	}
}

void CollisionEvent::TriggerStay(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnTriggerStay(collider, result);
	}
}

void CollisionEvent::TriggerExit(ColliderComponent* collider, hitResult& result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnTriggerExit(collider, result);
	}
}
