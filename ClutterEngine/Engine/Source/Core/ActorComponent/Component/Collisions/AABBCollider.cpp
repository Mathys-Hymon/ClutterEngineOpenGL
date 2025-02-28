#include "pch.h"  
#include <Core/ActorComponent/Components/Collisions/AABBCollider.h>  
#include <Core/ActorComponent/Components/Collisions/CircleCollider.h>  


using namespace clt;

AABBCollider::AABBCollider(Vector2 pBoxExtend) : mBoxExtend(pBoxExtend)  
{  
   mType = Type::AABB;  
}  

AABBCollider::AABBCollider(float pBoxExtend) : mBoxExtend(pBoxExtend)  
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
    auto pointsA = GetTransformedPoints();
    auto pointsB = pOther->GetTransformedPoints();

    float minOverlap = FLT_MAX;
    Vector2 smallestAxis;
    bool collisionFound = false;

    auto testAxes = [&](const std::array<Vector2, 4>& poly1, const std::array<Vector2, 4>& poly2)
        {
            for (size_t i = 0; i < poly1.size(); i++)
            {
                Vector2 edge = poly1[(i + 1) % poly1.size()] - poly1[i];
                Vector2 axis(-edge.y, edge.x);
                axis = axis.Normalized();

                auto project = [](const std::array<Vector2, 4>& points, const Vector2& axis)
                    {
                        float min = FLT_MAX, max = -FLT_MAX;
                        for (const auto& point : points)
                        {
                            float proj = Vector2::Dot(point, axis);
                            min = std::min(min, proj);
                            max = std::max(max, proj);
                        }
                        return std::make_pair(min, max);
                    };

                auto projA = project(pointsA, axis);
                auto projB = project(pointsB, axis);

                if (projA.second < projB.first || projB.second < projA.first)
                    return false;

                float overlap = std::min(projA.second - projB.first, projB.second - projA.first);
                if (overlap < minOverlap)
                {
                    minOverlap = overlap;
                    smallestAxis = axis;
                    collisionFound = true;
                }
            }
            return true;
        };

    if (!testAxes(pointsA, pointsB)) return false;
    if (!testAxes(pointsB, pointsA)) return false;

    if (!collisionFound) return false;

    // Déterminer la direction de la normale
    Vector2 centerA = (pointsA[0] + pointsA[1] + pointsA[2] + pointsA[3]) / 4.0f;
    Vector2 centerB = (pointsB[0] + pointsB[1] + pointsB[2] + pointsB[3]) / 4.0f;
    Vector2 dir = (centerB - centerA).Normalized();
    if (Vector2::Dot(dir, smallestAxis) < 0)
    {
        smallestAxis = -smallestAxis;
    }

    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<AABBCollider*>(this);
    outResult.ColliderB = pOther;
    outResult.IsColliding = true;
    outResult.Penetration = minOverlap;
    outResult.Normal = smallestAxis;
    outResult.Point = (centerA + centerB) * 0.5f;

    return true;
}

bool AABBCollider::CheckAABBvsCircle(CircleCollider* pOther, hitResult& outResult) const  
{  
   return false;  
}  

std::array<Vector2, 4> clt::AABBCollider::GetTransformedPoints() const  
{  
   Transform2D transform = GetWorldTransform();  
   Vector2 halfSize = mBoxExtend * transform.scale * 0.5f;  

   std::array<Vector2, 4> points = {  
       Vector2(-halfSize.x, -halfSize.y),  
       Vector2(halfSize.x, -halfSize.y),  
       Vector2(halfSize.x, halfSize.y),  
       Vector2(-halfSize.x, halfSize.y)  
   };  

   float radians = Maths::ToRad(transform.rotation);
   float cos = std::cos(radians);  
   float sin = std::sin(radians);  

   for (auto& point : points) {  
       point = Vector2(  
           point.x * cos - point.y * sin,  
           point.x * sin + point.y * cos  
       ) + transform.location;  
   }
   return points;  
}
