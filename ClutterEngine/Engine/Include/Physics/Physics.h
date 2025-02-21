#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>
#include <Physics/Collision/CollisionEvent.h>

namespace clt
{
	class CLUTTER_API Physics
	{
		std::map<Collider2DComponent*, CollisionEvent*> mColliderEvent;

	public:
		Physics();
		~Physics();

		void AddCollider(Collider2DComponent* pCollider);
		void RemoveCollider(Collider2DComponent* pCollider);

		void SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener);

		void Update();
	};
}