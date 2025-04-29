#include "pch.h"
#include "SphereCollider.h"
#include "OBBCollider.h"

using namespace clt;

bool SphereCollider::CheckSphereVsSphere(SphereCollider* pOther, hitResult& outResult) const
{
    if (!pOther)
        return false;

    // Retrieve the centers and radii (taking into account scaling; assuming uniform scaling for spheres)
    Vector3 centerA = GetWorldLocation();
    Vector3 centerB = pOther->GetWorldLocation();
    float radiusA = mRadius * GetWorldScale().x;
    float radiusB = pOther->GetRadius() * pOther->GetWorldScale().x;

    // Compute the vector and squared distance between the centers
    Vector3 diff = centerB - centerA;
    float distSq = diff.LengthSq();
    float radiusSum = radiusA + radiusB;

    if (distSq > radiusSum * radiusSum)
    {
        // No collision: draw the spheres in red for debugging
        DebugDraw::Get().DrawSphere(centerA, radiusA, Color::Red, 2);
        DebugDraw::Get().DrawSphere(centerB, radiusB, Color::Red, 2);
        return false;
    }

    float distance = std::sqrt(distSq);
    float penetration = radiusSum - distance;

    // Compute the collision normal
    Vector3 normal;
    if (distance > 1e-6f)
        normal = diff / distance;
    
    else normal = Vector3(1, 0, 0);

    // Compute a contact point (for example, on the surface of sphere A)
    Vector3 contactPoint = centerA + normal * (radiusA - penetration * 0.5f);

    // Fill the hitResult structure with collision details
    outResult.Normal = normal;
    outResult.Penetration = penetration;
    outResult.Point = contactPoint;
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<SphereCollider*>(this);
    outResult.ColliderB = pOther;

    // Debug: draw the contact point as a small sphere
    DebugDraw::Get().DrawSphere(contactPoint, 0.01f, Color::Red, 5);

    return true;
}

SphereCollider::SphereCollider(float radius) : mRadius(radius)
{
    mType = ColliderType::Sphere;

    mRadius /= 10;
}

bool SphereCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
    if (pOther->GetType() == ColliderType::OBB)
    {
        OBBCollider* other = static_cast<OBBCollider*>(pOther);
        if (other == nullptr) return false;

        return other->CheckOBBvsSphere(const_cast<SphereCollider*>(this), outResult);
    }
    else if (pOther->GetType() == ColliderType::Sphere) return CheckSphereVsSphere(static_cast<SphereCollider*>(pOther), outResult);
    return false;
}
