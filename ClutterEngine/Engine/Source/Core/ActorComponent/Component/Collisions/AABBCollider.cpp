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
	return false;
}