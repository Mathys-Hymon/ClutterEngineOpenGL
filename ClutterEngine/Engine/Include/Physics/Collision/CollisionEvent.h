#pragma once
#include <Physics/Collision/ICollisionListener.h>
#include <vector>

namespace clt
{
	class CLUTTER_API CollisionEvent
	{
		std::vector<ICollisionListener*> mListeners;

	public:
		CollisionEvent() = default;
		~CollisionEvent();

		void Subscribe(ICollisionListener* pListener);
		void UnSubscribe(ICollisionListener* pListener);

		void NotifyEnter(hitResult2D& result);
		void NotifyStay(hitResult2D& result);
		void NotifyExit(hitResult2D& result);
	};
}