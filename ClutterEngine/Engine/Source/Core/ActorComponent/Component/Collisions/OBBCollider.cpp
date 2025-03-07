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
    auto axesAtransform = GetWorldTransform();
    auto axesBtransform = pOther->GetWorldTransform();

    Vector3 axesA[3] = 
    {
    axesAtransform.Right(),
    axesAtransform.Up(),
    axesAtransform.Forward()
    };

    Vector3 axesB[3] =
    {
    axesBtransform.Right(),
    axesBtransform.Up(),
    axesBtransform.Forward()
    };

    float minOverlap = FLT_MAX;

    for (int i = 0; i < 3; i++) 
    {
        if (!TestAxis(axesA[i], pOther, minOverlap, outResult)) return false;
        if (!TestAxis(axesB[i], pOther, minOverlap, outResult)) return false;
    }

    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            Vector3 cross = Vector3::Cross(axesA[i], axesB[j]);
            if (cross.LengthSq() > 0.001f) 
            {
                if (!TestAxis(cross.Normalized(), pOther, minOverlap, outResult)) return false;
            }
        }
    }

    outResult.Penetration = minOverlap;
    outResult.ColliderA = const_cast<OBBCollider*>(this);
    outResult.ColliderB = pOther;
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();

    return true;
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


bool OBBCollider::TestAxis(const Vector3& pAxis, OBBCollider* pOther, float& minOverlap, hitResult& outResult) const
{
    float projA = Vector3::Dot(GetWorldLocation(), pAxis);
    float projB = Vector3::Dot(pOther->GetWorldLocation(), pAxis);

    float radiusA = GetProjectionRadius(pAxis);
    float radiusB = pOther->GetProjectionRadius(pAxis);

    float minA = projA - radiusA;
    float maxA = projA + radiusA;
    float minB = projB - radiusB;
    float maxB = projB + radiusB;

    if (maxA < minB || maxB < minA) return false;

    float overlap = std::min(maxA - minB, maxB - minA);

    if (overlap < minOverlap) 
    {
        minOverlap = overlap;
        Vector3 dirToB = (pOther->GetWorldLocation() - GetWorldLocation()).Normalized();

        if (Vector3::Dot(dirToB, pAxis) < 0) outResult.Normal = -pAxis;
        else outResult.Normal = pAxis;
    }
    return true;
}

float OBBCollider::GetProjectionRadius(const Vector3& axis) const
{
    return mBoxExtend.x * std::abs(Vector3::Dot(GetWorldTransform().Right()  , axis)) +
           mBoxExtend.y * std::abs(Vector3::Dot(GetWorldTransform().Up()     , axis)) +
           mBoxExtend.z * std::abs(Vector3::Dot(GetWorldTransform().Forward(), axis));
}