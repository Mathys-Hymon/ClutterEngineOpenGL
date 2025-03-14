#pragma once
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>

namespace clt
{
	class OBBCollider;
	class CLUTTER_API SphereCollider : public ColliderComponent
	{
		bool CheckSphereVsSphere(SphereCollider* pOther, hitResult& outResult) const;

		float mRadius;
	public:

		SphereCollider(float radius = 10.0f);

		~SphereCollider() = default;

		void  SetRadius(float radius) { mRadius = radius; };
		float GetRadius() const       { return mRadius;   };

		bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const override;
	};
}