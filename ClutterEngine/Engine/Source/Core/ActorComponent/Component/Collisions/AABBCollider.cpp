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
   Transform2D worldTransformA = GetWorldTransform();  
   Transform2D worldTransformB = pOther->GetWorldTransform();  

   Vector2 halfSizeA = mBoxExtend * worldTransformA.scale * 0.5f;  
   Vector2 halfSizeB = pOther->mBoxExtend * worldTransformB.scale * 0.5f;  

   Vector2 delta = worldTransformB.location - worldTransformA.location;  
   Vector2 overlap{ (halfSizeA.x + halfSizeB.x) - std::abs(delta.x),  
     (halfSizeA.y + halfSizeB.y) - std::abs(delta.y) };  

   if (overlap.x > 0 && overlap.y > 0)  
   {  
       outResult.ActorA = GetOwner();  
       outResult.ActorB = pOther->GetOwner();  
       outResult.ColliderA = const_cast<AABBCollider*>(this);  
       outResult.ColliderB = pOther;  
       outResult.IsColliding = true;  
       outResult.Penetration = (overlap.x < overlap.y) ? overlap.x : overlap.y;  
       outResult.Normal = (overlap.x < overlap.y) ?  
           Vector2(delta.x > 0 ? 1.0f : -1.0f, 0.0f) :  
           Vector2(0.0f, delta.y > 0 ? 1.0f : -1.0f);  

       // Calculate the point of collision  
       Vector2 collisionPoint = worldTransformA.location + (outResult.Normal * halfSizeA);  
       outResult.Point = collisionPoint;  

       return true;  
   }  
   return false;  
}

bool AABBCollider::CheckAABBvsCircle(CircleCollider* pOther, hitResult& outResult) const
{
	return false;
}
