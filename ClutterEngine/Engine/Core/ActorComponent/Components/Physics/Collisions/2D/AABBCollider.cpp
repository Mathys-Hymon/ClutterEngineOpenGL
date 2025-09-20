#include "pch.h"  
#include <Core/ActorComponent/Components/Physics/Collisions/2D/AABBCollider.h>  
#include <Core/ActorComponent/Components/Physics/Collisions/2D/CircleCollider.h>  


using namespace clt;

AABBCollider::AABBCollider(Vector2 pBoxExtend) : mBoxExtend(pBoxExtend)  
{  
   mType = ColliderType::AABB;  
}  

AABBCollider::AABBCollider(float pBoxExtend) : mBoxExtend(pBoxExtend)  
{  
   mType = ColliderType::AABB;  
}  

bool AABBCollider::CheckCollision(ColliderComponent* pOther, HitResult& outResult) const  
{  
   if (pOther->GetType() == ColliderType::AABB)  
   {  
       return CheckAABBvsAABB(static_cast<AABBCollider*>(pOther), outResult);  
   }  
   else  
   {  
       return CheckAABBvsCircle(static_cast<CircleCollider*>(pOther), outResult);  
   }  
}  

bool AABBCollider::CheckAABBvsAABB(AABBCollider* pOther, HitResult& outResult) const 
{
    // Get the transformed points of both AABBs
    auto pointsA = GetTransformedPoints();
    auto pointsB = pOther->GetTransformedPoints();

    float minOverlap = FLT_MAX;
    Vector2 smallestAxis;
    bool collisionFound = false;

    // Lambda function to test axes for overlap
    auto testAxes = [&](const std::array<Vector2, 4>& poly1, const std::array<Vector2, 4>& poly2) {
        for (size_t i = 0; i < poly1.size(); i++) {
            // Calculate the edge and its perpendicular axis
            Vector2 edge = poly1[(i + 1) % poly1.size()] - poly1[i];
            Vector2 axis(-edge.y, edge.x);
            axis = axis.Normalized();

            // Lambda function to project points onto an axis
            auto project = [](const std::array<Vector2, 4>& points, const Vector2& axis) {
                float min = FLT_MAX, max = -FLT_MAX;
                for (const auto& point : points) {
                    float proj = Vector2::Dot(point, axis);
                    min = std::min(min, proj);
                    max = std::max(max, proj);
                }
                return std::make_pair(min, max);
            };

            // Project both polygons onto the axis
            auto projA = project(pointsA, axis);
            auto projB = project(pointsB, axis);

            // Check for overlap
            if (projA.second < projB.first || projB.second < projA.first)
                return false;

            // Calculate the overlap
            float overlap = std::min(projA.second - projB.first, projB.second - projA.first);
            if (overlap < minOverlap) {
                minOverlap = overlap;
                smallestAxis = axis;
                collisionFound = true;
            }

            // Calculate the centers of both polygons
            Vector2 centerA = (pointsA[0] + pointsA[1] + pointsA[2] + pointsA[3]) / 4.0f;
            Vector2 centerB = (pointsB[0] + pointsB[1] + pointsB[2] + pointsB[3]) / 4.0f;

            // Determine the direction to B
            Vector2 dirToB = (centerB - centerA).Normalized();

            // Ensure the smallest axis points in the correct direction
            if (Vector2::Dot(dirToB, smallestAxis) < 0) {
                smallestAxis = -smallestAxis;
            }
        }
        return true;
    };

    // Test axes of both polygons
    if (!testAxes(pointsA, pointsB)) return false;
    if (!testAxes(pointsB, pointsA)) return false;

    if (!collisionFound) return false;

    std::vector<Vector2> contactPoints;

    // Find contact points by checking line segment intersections
    for (size_t i = 0; i < pointsA.size(); i++) {
        Vector2 p1 = pointsA[i];
        Vector2 p2 = pointsA[(i + 1) % pointsA.size()];

        for (size_t j = 0; j < pointsB.size(); j++) {
            Vector2 p3 = pointsB[j];
            Vector2 p4 = pointsB[(j + 1) % pointsB.size()];

            float denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
            if (denom != 0)
            {
                float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
                float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;

                if (!(ua < 0 || ua > 1 || ub < 0 || ub > 1))
                {
                    Vector2 intersection;

                    intersection.x = p1.x + ua * (p2.x - p1.x);
                    intersection.y = p1.y + ua * (p2.y - p1.y);

                    contactPoints.push_back(intersection);
                }
            }
        }
    }

    // If no contact points found, find the closest points
    if (contactPoints.empty()) 
    {
        Vector2 closestA, closestB;
        float minDistSq = FLT_MAX;
        for (const auto& pA : pointsA) 
        {
            for (const auto& pB : pointsB) 
            {
                float distSq = (pA - pB).LengthSquared();

                if (distSq < minDistSq) 
                {
                    minDistSq = distSq;
                    closestA = pA;
                    closestB = pB;
                }
            }
        }
        outResult.Point = (closestA + closestB) * 0.5f;
    }
    else {
        outResult.Point = contactPoints[0];
    }

    // Set the collision result
    outResult.Normal = smallestAxis;
    outResult.Penetration = minOverlap;
    outResult.ColliderA = const_cast<AABBCollider*>(this);
    outResult.ColliderB = pOther;
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();

    return true;
}

bool AABBCollider::CheckAABBvsCircle(CircleCollider* pOther, HitResult& outResult) const  
{  
    return false;
}  

std::array<Vector2, 4> clt::AABBCollider::GetTransformedPoints() const  
{  
   Transform transform = GetWorldTransform();  
   Vector2 halfSize = mBoxExtend * transform.Scale().xy() * 0.5f;  

   std::array<Vector2, 4> points = {  
       Vector2(-halfSize.x, -halfSize.y),  
       Vector2(halfSize.x, -halfSize.y),  
       Vector2(halfSize.x, halfSize.y),  
       Vector2(-halfSize.x, halfSize.y)  
   };  

   float radians = Maths::ToRad(transform.Rotation().z);
   float cos = std::cos(radians);  
   float sin = std::sin(radians);  

   for (auto& point : points) {  
       point = Vector2(  
           point.x * cos - point.y * sin,  
           point.x * sin + point.y * cos  
       ) + transform.Location().xy();  
   }
   return points;  
}
