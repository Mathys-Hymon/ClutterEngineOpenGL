#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>

using namespace clt;

void AABBCollider::CollisionEnter(std::vector<Collider2DComponent*> pColliders)
{
}

AABBCollider::AABBCollider(Vector2 pBoxExtend)
{
}

bool AABBCollider::CheckCollision(Collider2DComponent* pOther)
{
	return false;
}
