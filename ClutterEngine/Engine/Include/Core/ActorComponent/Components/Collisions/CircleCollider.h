#pragma once
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>

namespace clt
{
	class CLUTTER_API CircleCollider : public Collider2DComponent
	{
		bool CheckSphereCollision(Collider2DComponent* pOther);
		bool CheckSphereBoxCollision(Collider2DComponent* pOther);

	public:
		 CircleCollider();
		~CircleCollider() = default;

		virtual bool CheckCollision(Collider2DComponent* pOther) override;
	};
}