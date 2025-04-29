#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/OBBCollider.h>
#include <Core/ActorComponent/Components/Collisions/SphereCollider.h>

using namespace clt;

OBBCollider::OBBCollider(Vector3 pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = ColliderType::OBB;

    mBoxExtend /= 10;
}

OBBCollider::OBBCollider(float pBoxExtend) : ColliderComponent(), mBoxExtend(pBoxExtend)
{
	mType = ColliderType::OBB;

    mBoxExtend /= 10;
}

bool OBBCollider::CheckOBBvsOBB(OBBCollider* pOther, hitResult& outResult) const
{
    if (!pOther)
    {
        DebugDraw::Get().DrawBox(GetWorldLocation(), mBoxExtend * GetWorldScale(), Color::Green, 2, GetWorldRotation());
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

        Vector3 scaleB = pOther->GetWorldScale();
        Vector3 scaledExtentsB = Vector3(std::abs(scaleB.x) * pOther->mBoxExtend.x,
            std::abs(scaleB.y) * pOther->mBoxExtend.y,
            std::abs(scaleB.z) * pOther->mBoxExtend.z);

        float projB = scaledExtentsB.x * std::abs(Vector3::Dot(axesB[0], nAxis)) +
            scaledExtentsB.y * std::abs(Vector3::Dot(axesB[1], nAxis)) +
            scaledExtentsB.z * std::abs(Vector3::Dot(axesB[2], nAxis));

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
            DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::Red, 2, GetWorldRotation());
            DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::Red, 2, pOther->GetWorldRotation());
            return false;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        if (!TestAxis(axesB[i]))
        {
            DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::Red, 2, GetWorldRotation());
            DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::Red, 2, pOther->GetWorldRotation());
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
                DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::Red, 2, GetWorldRotation());
                DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::Red, 2, pOther->GetWorldRotation());
                return false;
            }
        }
    }

    outResult.Normal = smallestAxis;
    outResult.Penetration = minOverlap;
    outResult.Point = ComputeHitPoint(pOther);
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<OBBCollider*>(this);
    outResult.ColliderB = pOther;

    DebugDraw::Get().DrawBox(outResult.Point, 0.01f, Color::Red, 5);

    DebugDraw::Get().DrawBox(centerA, mBoxExtend * GetWorldScale(), Color::Green, 2, GetWorldRotation());
    DebugDraw::Get().DrawBox(centerB, pOther->mBoxExtend * pOther->GetWorldScale(), Color::Green, 2, pOther->GetWorldRotation());

    return true;
}

bool OBBCollider::CheckOBBvsSphere(SphereCollider* pOther, hitResult& outResult) const
{
    if (!pOther)
        return false;

    // Retrieve the sphere's center and radius
    Vector3 sphereCenter = pOther->GetWorldLocation();
    // Assuming GetWorldScale() returns a vector with a uniform factor for the radius
    float sphereRadius = pOther->GetRadius() * pOther->GetWorldScale().x;

    // Retrieve the OBB's center and its axes
    Vector3 obbCenter = GetWorldLocation();
    Vector3 axes[3];
    GetOBBAxis(axes);

    // Compute the vector between the sphere center and the OBB center
    Vector3 d = sphereCenter - obbCenter;
    Vector3 closestPoint = obbCenter;

    // Calculate the half-extents of the OBB considering its scale
    Vector3 scale = GetWorldScale();
    Vector3 extents(std::abs(scale.x) * mBoxExtend.x,
        std::abs(scale.y) * mBoxExtend.y,
        std::abs(scale.z) * mBoxExtend.z);

    // For each OBB axis, clamp the projection of 'd' onto the axis and add the corresponding contribution
    {
        float proj = Vector3::Dot(d, axes[0]);
        float clamped = std::max(-extents.x, std::min(proj, extents.x));
        closestPoint += axes[0] * clamped;
    }
    {
        float proj = Vector3::Dot(d, axes[1]);
        float clamped = std::max(-extents.y, std::min(proj, extents.y));
        closestPoint += axes[1] * clamped;
    }
    {
        float proj = Vector3::Dot(d, axes[2]);
        float clamped = std::max(-extents.z, std::min(proj, extents.z));
        closestPoint += axes[2] * clamped;
    }

    // Compute the vector from the sphere center to the closest point on the OBB and its squared distance
    Vector3 v = sphereCenter - closestPoint;
    float distSq = v.LengthSq();

    if (distSq > sphereRadius * sphereRadius)
    {
        // No collision: draw the OBB in red for debugging
        DebugDraw::Get().DrawBox(obbCenter, mBoxExtend * GetWorldScale(), Color::Red, 2, GetWorldRotation());
        return false;
    }

    float distance = std::sqrt(distSq);
    float penetration = sphereRadius - distance;

    // Compute the collision normal
    Vector3 normal;
    if (distance > 1e-6f)
        normal = v / distance;

    else normal = Vector3(1, 0, 0); // Arbitrary normal
        
    outResult.Normal = normal;
    outResult.Penetration = penetration;
    outResult.Point = closestPoint;
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<OBBCollider*>(this);
    outResult.ColliderB = pOther;

    // Debug: draw the contact point
    DebugDraw::Get().DrawBox(closestPoint, 0.01f, Color::Red, 5);

    return true;
}

void OBBCollider::GetOBBAxis(Vector3(&axes)[3]) const
{
	axes[0] = GetWorldTransform().Right();
	axes[1] = GetWorldTransform().Up();
	axes[2] = GetWorldTransform().Forward();
}

Vector3 OBBCollider::ComputeHitPoint(const OBBCollider* boxB) const
{
    std::vector<Vector3> contactPoints;

    auto GetOBBVertices = [](const OBBCollider* box) -> std::vector<Vector3>
        {
            std::vector<Vector3> vertices;
            Vector3 center = box->GetWorldLocation();
            Vector3 axes[3];
            box->GetOBBAxis(axes);

            Vector3 scale = box->GetWorldScale();
            Vector3 extents = Vector3(std::abs(scale.x) * box->mBoxExtend.x,
                std::abs(scale.y) * box->mBoxExtend.y,
                std::abs(scale.z) * box->mBoxExtend.z);

            for (int x = -1; x <= 1; x += 2)
            {
                for (int y = -1; y <= 1; y += 2)
                {
                    for (int z = -1; z <= 1; z += 2)
                    {
                        vertices.push_back(center +
                            axes[0] * (x * extents.x) +
                            axes[1] * (y * extents.y) +
                            axes[2] * (z * extents.z));
                    }
                }
            }
            return vertices;
        };

    auto IsPointInsideOBB = [](const Vector3& point, const OBBCollider* box) -> bool
        {
            Vector3 center = box->GetWorldLocation();
            Vector3 d = point - center;
            Vector3 axes[3];
            box->GetOBBAxis(axes);

            Vector3 scale = box->GetWorldScale();
            Vector3 extents = Vector3(std::abs(scale.x) * box->mBoxExtend.x,
                std::abs(scale.y) * box->mBoxExtend.y,
                std::abs(scale.z) * box->mBoxExtend.z);

            for (int i = 0; i < 3; ++i)
            {
                if (std::abs(Vector3::Dot(d, axes[i])) > (i == 0 ? extents.x : (i == 1 ? extents.y : extents.z)))
                    return false;
            }
            return true;
        };

    for (const auto& v : GetOBBVertices(this))
    {
        if (IsPointInsideOBB(v, boxB))
            contactPoints.push_back(v);
    }

    for (const auto& v : GetOBBVertices(boxB))
    {
        if (IsPointInsideOBB(v, this))
            contactPoints.push_back(v);
    }

    if (contactPoints.empty())
        return GetWorldLocation() + (boxB->GetWorldLocation() - GetWorldLocation()) * 0.5f;

    Vector3 centroid(0, 0, 0);
    for (const auto& cp : contactPoints)
    {
        centroid += cp;
    }
    return centroid / static_cast<float>(contactPoints.size());
}

bool OBBCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == ColliderType::OBB) return CheckOBBvsOBB(static_cast<OBBCollider*>(pOther), outResult);
	else if (pOther->GetType() == ColliderType::Sphere) return CheckOBBvsSphere(static_cast<SphereCollider*>(pOther), outResult);

	return false;
}
