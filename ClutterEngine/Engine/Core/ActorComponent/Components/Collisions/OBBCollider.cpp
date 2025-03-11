#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>

using namespace clt;

OBBCollider::OBBCollider(Vector3 pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend / 10)
{
	mType = Type::OBB;
}

OBBCollider::OBBCollider(float pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend / 10)
{
	mType = Type::OBB;
}

bool OBBCollider::CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const
{
    if (!pOther) return false;

 	Vector3 centerA = GetWorldLocation();
	Vector3 centerB = pOther->GetOwner()->GetActorLocation();

	Vector3 axesA[3];
	Vector3 axesB[3];

	GetOBBAxis(axesA);
	pOther->GetOBBAxis(axesB);

	Vector3 t = centerB - centerA;
	float minOverlap = FLT_MAX;

	Vector3 smallestAxis;

    auto TestAxis = [&](const Vector3& axis) -> bool {
        if (axis.LengthSq() < 1e-6f)
            return true;
        Vector3 nAxis = axis.Normalized();

        float projA =
            std::abs(Vector3::Dot(mBoxExtend * GetWorldScale(), Vector3(
                std::abs(Vector3::Dot(axesA[0], nAxis)),
                std::abs(Vector3::Dot(axesA[1], nAxis)),
                std::abs(Vector3::Dot(axesA[2], nAxis))
            )));
        float projB =
            std::abs(Vector3::Dot(pOther->mBoxExtend * GetWorldScale(), Vector3(
                std::abs(Vector3::Dot(axesB[0], nAxis)),
                std::abs(Vector3::Dot(axesB[1], nAxis)),
                std::abs(Vector3::Dot(axesB[2], nAxis))
            )));
        float distance = std::abs(Vector3::Dot(t, nAxis));

        if (distance > projA + projB)
            return false;

        float overlap = (projA + projB) - distance;
        if (overlap < minOverlap)
        {
            minOverlap = overlap;
            smallestAxis = nAxis;
            if (Vector3::Dot(t, smallestAxis) < 0)
                smallestAxis = smallestAxis * -1.0f;
        }
        return true;
        };

    for (int i = 0; i < 3; ++i)
    {
        if (!TestAxis(axesA[i]))
            return false;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (!TestAxis(axesB[i]))
            return false;
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Vector3 axis = Vector3::Cross(axesA[i], axesB[j]);
            if (!TestAxis(axis))
                return false;
        }
    }

    outResult.Normal = smallestAxis;
    outResult.Penetration = minOverlap;
    outResult.Point = centerA + (t * 0.5f);
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<OBBCollider*>(this);
    outResult.ColliderB = pOther;

    return true;
}

bool OBBCollider::CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const
{
	return false;
}

void OBBCollider::GetOBBAxis(Vector3(&axes)[3]) const
{
	axes[0] = GetWorldTransform().Forward();
	axes[1] = GetWorldTransform().Right();
	axes[2] = GetWorldTransform().Up();
}

bool OBBCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == Type::OBB) return CheckOBBvsOBB(static_cast<OBBCollider*>(pOther), outResult);
	else if (pOther->GetType() == Type::Sphere) return CheckOBBvsSphere(static_cast<SphereCollider*>(pOther), outResult);

	return false;
}
