#pragma once
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>

namespace clt
{
	class CLUTTER_API CircleCollider : public ColliderComponent
	{
		float mRadius;

		bool CheckCircleVsCircle(CircleCollider* pOther, hitResult& outResult) const;

	public:
		 CircleCollider(float pRadius = 32);
		~CircleCollider() = default;

		float GetRadius() const { return mRadius; };

		bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const override;
	};
}