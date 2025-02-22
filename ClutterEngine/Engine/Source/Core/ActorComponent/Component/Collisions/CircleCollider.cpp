#include "pch.h"
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>

using namespace clt;

CircleCollider::CircleCollider(float pRadius) : mRadius(pRadius)
{
	mType = Type::Circle;
}

bool CircleCollider::CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const
{
	return false;
}
