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

		void NotifyEnter(ColliderComponent* collider, hitResult& result);
		void NotifyStay(ColliderComponent* collider, hitResult& result);
		void NotifyExit(ColliderComponent* collider, hitResult& result);

		void TriggerEnter(ColliderComponent* collider, hitResult& result);
		void TriggerStay(ColliderComponent* collider, hitResult& result);
		void TriggerExit(ColliderComponent* collider, hitResult& result);
	};
}