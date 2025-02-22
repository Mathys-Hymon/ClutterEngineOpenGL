#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>

using namespace clt;

AABBCollider::AABBCollider(Vector2 pBoxExtend) : mBoxExtend(pBoxExtend)
{
	mType = Type::AABB;
}

bool AABBCollider::CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const
{
	if (pOther->GetType() == Type::AABB)
	{
		return CheckAABBvsAABB(static_cast<AABBCollider*>(pOther), outResult);
	}
	else
	{
		return CheckAABBvsCircle(static_cast<CircleCollider*>(pOther), outResult);
	}
}

bool AABBCollider::CheckAABBvsAABB(AABBCollider* pOther, hitResult& outResult) const
{
	return false;
}

bool AABBCollider::CheckAABBvsCircle(CircleCollider* pOther, hitResult& outResult) const
{
	return false;
}
