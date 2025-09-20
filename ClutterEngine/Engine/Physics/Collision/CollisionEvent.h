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

		void NotifyEnter(ColliderComponent* collider, HitResult& result);
		void NotifyStay(ColliderComponent* collider, HitResult& result);
		void NotifyExit(ColliderComponent* collider, HitResult& result);

		void TriggerEnter(ColliderComponent* collider, HitResult& result);
		void TriggerStay(ColliderComponent* collider, HitResult& result);
		void TriggerExit(ColliderComponent* collider, HitResult& result);
	};
}