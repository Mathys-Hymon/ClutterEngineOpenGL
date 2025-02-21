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

void CollisionEvent::Notify(hitResult result)
{
	for (ICollisionListener* listener : mListeners)
	{
		listener->OnNotify(result);
	}	
}
