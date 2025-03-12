#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>

using namespace clt;

OBBCollider::OBBCollider(Vector3 pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = Type::OBB;

    mBoxExtend /= 10;
}

OBBCollider::OBBCollider(float pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = Type::OBB;

    mBoxExtend /= 10;
}

bool OBBCollider::CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const
{
    if (!pOther)
    {
        DebugDraw::Get().DrawBox(GetWorldLocation(), mBoxExtend * GetWorldScale(), Color::green, 2, GetWorldRotation());
        return false;
    }


 	Vector3 centerA = GetWorldLocation();
	Vector3 centerB = pOther->GetWorldLocation();

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

        Vector3 scaleA = GetWorldScale();
        Vector3 scaledExtentsA = Vector3(std::abs(scaleA.x) * mBoxExtend.x,
            std::abs(scaleA.y) * mBoxExtend.y,
            std::abs(scaleA.z) * mBoxExtend.z);

        float projA = scaledExtentsA.x * std::abs(Vector3::Dot(axesA[0], nAxis)) +
            scaledExtentsA.y * std::abs(Vector3::Dot(axesA[1], nAxis)) +
            scaledExtentsA.z * std::abs(Vector3::Dot(axesA[2], nAxis));

        // Calcul pour la boîte B
        Vector3 scaleB = pOther->GetWorldScale();
        Vector3 scaledExtentsB = Vector3(std::abs(scaleB.x) * pOther->mBoxExtend.x,
            std::abs(scaleB.y) * pOther->mBoxExtend.y,
            std::abs(scaleB.z) * pOther->mBoxExtend.z);

        float projB = scaledExtentsB.x * std::abs(Vector3::Dot(axesB[0], nAxis)) +
            scaledExtentsB.y * std::abs(Vector3::Dot(axesB[1], nAxis)) +
            scaledExtentsB.z * std::abs(Vector3::Dot(axesB[2], nAxis));

        // Projection du vecteur de séparation sur nAxis
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
        {
            DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::red, 2, GetWorldRotation());
            DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::red, 2, pOther->GetWorldRotation());
            return false;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        if (!TestAxis(axesB[i]))
        {
            DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::red, 2, GetWorldRotation());
            DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::red, 2, pOther->GetWorldRotation());
            return false;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Vector3 axis = Vector3::Cross(axesA[i], axesB[j]);
            if (!TestAxis(axis))
            {
                DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::red, 2, GetWorldRotation());
                DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::red, 2, pOther->GetWorldRotation());
                return false;
            }
        }
    }

    outResult.Normal = smallestAxis;
    outResult.Penetration = minOverlap;
    outResult.Point = centerA + (t * 0.5f);
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<OBBCollider*>(this);
    outResult.ColliderB = pOther;

    DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::green, 2, GetWorldRotation());
    DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::green, 2, pOther->GetWorldRotation());

    return true;
}

bool OBBCollider::CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const
{
	return false;
}

void OBBCollider::GetOBBAxis(Vector3(&axes)[3]) const
{
	axes[0] = GetWorldTransform().Right();
	axes[1] = GetWorldTransform().Up();
	axes[2] = GetWorldTransform().Forward();
}

bool OBBCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == Type::OBB) return CheckOBBvsOBB(static_cast<OBBCollider*>(pOther), outResult);
	else if (pOther->GetType() == Type::Sphere) return CheckOBBvsSphere(static_cast<SphereCollider*>(pOther), outResult);

	return false;
}
