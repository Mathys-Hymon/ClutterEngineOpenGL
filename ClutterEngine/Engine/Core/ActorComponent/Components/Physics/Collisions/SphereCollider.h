#pragma once
#include <Core/ActorComponent/Components/Physics/Collisions/ColliderComponent.h>

namespace clt
{
	class OBBCollider;
	class CLUTTER_API SphereCollider : public ColliderComponent
	{
		bool CheckSphereVsSphere(SphereCollider* pOther, HitResult& outResult) const;

		float mRadius;
	public:

		SphereCollider(float radius = 10.0f);

		~SphereCollider() = default;

		void  SetRadius(float radius) { mRadius = radius; };
		float GetRadius() const       { return mRadius;   };

		bool CheckCollision(ColliderComponent* pOther, HitResult& outResult) const override;
	};
}