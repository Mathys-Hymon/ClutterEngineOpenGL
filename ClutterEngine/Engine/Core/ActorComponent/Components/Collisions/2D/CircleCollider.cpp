#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/2D/CircleCollider.h>
#include <Core/ActorComponent/Components/Collisions/2D/AABBCollider.h>

using namespace clt;

CircleCollider::CircleCollider(float pRadius) : mRadius(pRadius)
{
	mType = ColliderType::Circle;
}

bool CircleCollider::CheckCollision(ColliderComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == ColliderType::Circle)
	{
		return CheckCircleVsCircle(static_cast<CircleCollider*>(pOther), outResult);
	}
	else
	{
		auto* aabb = static_cast<AABBCollider*>(pOther);

		return aabb->CheckAABBvsCircle(const_cast<CircleCollider*>(this), outResult);
	}
}

bool CircleCollider::CheckCircleVsCircle(CircleCollider* pOther, hitResult& outResult) const
{
	CircleCollider* other = static_cast<CircleCollider*>(pOther);
	Vector2 delta = other->GetWorldLocation().xy() - GetWorldLocation().xy();
	float distance = delta.Length();
	float totalRadius = mRadius + other->mRadius;

	if (distance < totalRadius)
	{
		outResult.Normal = delta.Normalized();
		outResult.Penetration = totalRadius - distance;
		outResult.Point = GetWorldLocation().xy() + outResult.Normal * mRadius;
		return true;
	}
	return false;
}
