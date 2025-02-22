#pragma once
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>

namespace clt
{
	class CircleCollider;
	class CLUTTER_API AABBCollider : public Collider2DComponent
	{
		Vector2 mBoxExtend;

		bool CheckAABBvsAABB(AABBCollider* pOther, hitResult& outResult) const;
		bool CheckAABBvsCircle(CircleCollider* pOther, hitResult& outResult) const;

	public:
		 AABBCollider(Vector2 pBoxExtend = {64,64});
		~AABBCollider() = default;

		bool CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const override;

		friend CircleCollider;
	};
}