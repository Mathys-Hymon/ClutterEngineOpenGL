#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>

using namespace clt;

CircleCollider::CircleCollider()
{
}

bool CircleCollider::CheckCollision(Collider2DComponent* pOther)
{
	return false;
}

bool CircleCollider::CheckSphereCollision(Collider2DComponent* pOther)
{
	return false;
}

bool CircleCollider::CheckSphereBoxCollision(Collider2DComponent* pOther)
{
	return false;
}