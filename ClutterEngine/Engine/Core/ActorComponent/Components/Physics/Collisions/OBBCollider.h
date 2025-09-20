#pragma once
#include <Core/ActorComponent/Components/Physics/Collisions/ColliderComponent.h>
#include <array>

namespace clt
{
	class SphereCollider;
	class ClutterPhysics;
	class CLUTTER_API OBBCollider : public ColliderComponent
	{
		bool CheckOBBvsOBB(OBBCollider* pOther, HitResult& outResult) const;
		bool CheckOBBvsSphere(SphereCollider* pOther, HitResult& outResult) const;

		void GetOBBAxis(Vector3 (&axes)[3]) const;

		Vector3 ComputeHitPoint(const OBBCollider* boxB) const;

		Vector3 mBoxExtend;

		friend SphereCollider;
		friend ClutterPhysics;
	public:

		OBBCollider(Vector3 pBoxExtend);
		OBBCollider(float pBoxExtend = 10.0f);

		~OBBCollider() = default;

		void SetBoxExtend(Vector3 pBoxExtend) { mBoxExtend = pBoxExtend; };
		void SetBoxExtend(float   pBoxExtend) { mBoxExtend = pBoxExtend; };

		Vector3 GetBoxExtend() const { return mBoxExtend; };

		bool CheckCollision(ColliderComponent* pOther, HitResult& outResult) const override;
	};
}