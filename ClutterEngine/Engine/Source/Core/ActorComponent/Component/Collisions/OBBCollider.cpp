#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>

using namespace clt;

OBBCollider::OBBCollider(Vector3 pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = Type::OBB;
}

OBBCollider::OBBCollider(float pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = Type::OBB;
}

bool OBBCollider::CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const
{
	return false;
}

bool OBBCollider::CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const
{
	return false;
}

bool OBBCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == Type::OBB) return CheckOBBvsOBB(static_cast<OBBCollider*>(pOther), outResult);
	else if (pOther->GetType() == Type::Sphere) return CheckOBBvsSphere(static_cast<SphereCollider*>(pOther), outResult);

	return false;
}
