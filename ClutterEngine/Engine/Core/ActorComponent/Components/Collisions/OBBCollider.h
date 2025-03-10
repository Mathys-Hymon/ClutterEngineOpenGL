#pragma once
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>
#include <array>

namespace clt
{
	class SphereCollider;
	class CLUTTER_API OBBCollider : public ColliderComponent
	{
		bool CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const;
		bool CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const;

	public:
		Vector3 mBoxExtend;

		OBBCollider(Vector3 pBoxExtend = 1);
		OBBCollider(float pBoxExtend);

		~OBBCollider() = default;

		bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const override;
	};
}