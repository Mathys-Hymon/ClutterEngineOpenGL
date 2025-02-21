#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>

using namespace clt;

AABBCollider::AABBCollider(Vector2 pBoxExtend)
{
}

bool AABBCollider::CheckCollision(Collider2DComponent* pOther)
{
	if (dynamic_cast<AABBCollider*>(pOther))
	{
		return CheckBoxCollision(pOther);
	}
	else
	{
		return CheckBoxSphereCollision(pOther);
	}
}

bool AABBCollider::CheckBoxCollision(Collider2DComponent* pOther)
{
	return false;
}

bool AABBCollider::CheckBoxSphereCollision(Collider2DComponent* pOther)
{
	return false;
}