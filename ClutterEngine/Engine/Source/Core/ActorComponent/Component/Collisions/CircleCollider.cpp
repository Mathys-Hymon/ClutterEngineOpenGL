#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>

using namespace clt;

CircleCollider::CircleCollider(float pRadius) : mRadius(pRadius)
{
	mType = Type::Circle;
}

bool CircleCollider::CheckCollision(Collider2DComponent* pOther, hitResult2D& outResult) const
{
	if (pOther->GetType() == Type::Circle)
	{
		return CheckCircleVsCircle(static_cast<CircleCollider*>(pOther), outResult);
	}
	else
	{
		auto* aabb = static_cast<AABBCollider*>(pOther);

		return aabb->CheckAABBvsCircle(const_cast<CircleCollider*>(this), outResult);
	}
}

bool CircleCollider::CheckCircleVsCircle(CircleCollider* pOther, hitResult2D& outResult) const
{
	CircleCollider* other = static_cast<CircleCollider*>(pOther);
	Vector2 delta = other->GetWorldPosition().xy() - GetWorldPosition().xy();
	float distance = delta.Length();
	float totalRadius = mRadius + other->mRadius;

	if (distance < totalRadius)
	{
		outResult.Normal = delta.Normalized();
		outResult.Penetration = totalRadius - distance;
		outResult.Point = GetWorldPosition().xy() + outResult.Normal * mRadius;
		return true;
	}
	return false;
}
