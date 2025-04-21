#pragma once
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>
#include <array>

namespace clt
{
	class SphereCollider;
	class Physics;
	class CLUTTER_API OBBCollider : public ColliderComponent
	{
		bool CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const;
		bool CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const;

		void GetOBBAxis(Vector3 (&axes)[3]) const;

		Vector3 ComputeHitPoint(const OBBCollider* boxB) const;

		Vector3 mBoxExtend;

		friend SphereCollider;
		friend Physics;
	public:

		OBBCollider(Vector3 pBoxExtend);
		OBBCollider(float pBoxExtend = 10.0f);

		~OBBCollider() = default;

		void SetBoxExtend(Vector3 pBoxExtend) { mBoxExtend = pBoxExtend; };
		void SetBoxExtend(float   pBoxExtend) { mBoxExtend = pBoxExtend; };

		Vector3 GetBoxExtend() const { return mBoxExtend; };

		bool CheckCollision(ColliderComponent* pOther, hitResult& outResult) const override;
	};
}