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
    Vector2 minA(FLT_MAX), maxA(-FLT_MAX);
    Vector2 minB(FLT_MAX), maxB(-FLT_MAX);

    for (const auto& p : pointsA) {
        minA.x = std::min(minA.x, p.x);
        minA.y = std::min(minA.y, p.y);
        maxA.x = std::max(maxA.x, p.x);
        maxA.y = std::max(maxA.y, p.y);
    }
    for (const auto& p : pointsB) {
        minB.x = std::min(minB.x, p.x);
        minB.y = std::min(minB.y, p.y);
        maxB.x = std::max(maxB.x, p.x);
        maxB.y = std::max(maxB.y, p.y);
    }

    // Test SAT
    auto testAxes = [&](const std::array<Vector2, 4>& poly) {
        for (size_t i = 0; i < poly.size(); i++) {
            Vector2 edge = poly[(i + 1) % poly.size()] - poly[i];
            Vector2 axis(-edge.y, edge.x);
            axis = axis.Normalized();

            // Projection
            float minProjA = FLT_MAX, maxProjA = -FLT_MAX;
            for (const auto& p : pointsA) {
                float proj = Vector2::Dot(p, axis);
                minProjA = std::min(minProjA, proj);
                maxProjA = std::max(maxProjA, proj);
            }

            float minProjB = FLT_MAX, maxProjB = -FLT_MAX;
            for (const auto& p : pointsB) {
                float proj = Vector2::Dot(p, axis);
                minProjB = std::min(minProjB, proj);
                maxProjB = std::max(maxProjB, proj);
            }

            // Check overlap
            if (maxProjA < minProjB || maxProjB < minProjA)
                return false;

            float overlap = std::min(maxProjA - minProjB, maxProjB - minProjA);
            if (overlap < minOverlap) {
                minOverlap = overlap;
                smallestAxis = axis;
                collisionFound = true;
            }
        }
        return true;
    };

    if (!testAxes(pointsA)) return false;
    if (!testAxes(pointsB)) return false;


    Vector2 contactSum;
    int contactCount = 0;
    for (const auto& p : pointsA) {
        if (p.x >= minB.x && p.x <= maxB.x && p.y >= minB.y && p.y <= maxB.y) {
            contactSum += p;
            contactCount++;
        }
    }
    for (const auto& p : pointsB) {
        if (p.x >= minA.x && p.x <= maxA.x && p.y >= minA.y && p.y <= maxA.y) {
            contactSum += p;
            contactCount++;
        }
    }


    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();
    outResult.ColliderA = const_cast<AABBCollider*>(this);
    outResult.ColliderB = pOther;
    outResult.IsColliding = true;
    outResult.Penetration = minOverlap;
    outResult.Normal = smallestAxis;
    outResult.Point = contactCount > 0 ? contactSum / contactCount : (minA + maxA + minB + maxB) * 0.25f;
    

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
