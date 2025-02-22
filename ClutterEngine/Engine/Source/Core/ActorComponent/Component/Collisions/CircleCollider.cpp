#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>

using namespace clt;

CircleCollider::CircleCollider(float pRadius) : mRadius(pRadius)
{
	mType = Type::Circle;
}

bool CircleCollider::CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const
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

bool CircleCollider::CheckCircleVsCircle(CircleCollider* pOther, hitResult& outResult) const
{
	return false;
}
