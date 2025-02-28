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

bool AABBCollider::CheckAABBvsAABB(AABBCollider* pOther, hitResult& outResult) const {
    auto pointsA = GetTransformedPoints();
    auto pointsB = pOther->GetTransformedPoints();

    float minOverlap = FLT_MAX;
    Vector2 smallestAxis;
    bool collisionFound = false;

    auto testAxes = [&](const std::array<Vector2, 4>& poly1, const std::array<Vector2, 4>& poly2) {
        for (size_t i = 0; i < poly1.size(); i++) {
            Vector2 edge = poly1[(i + 1) % poly1.size()] - poly1[i];
            Vector2 axis(-edge.y, edge.x); // Axe perpendiculaire à l'arête
            axis = axis.Normalized();

            auto project = [](const std::array<Vector2, 4>& points, const Vector2& axis) {
                float min = FLT_MAX, max = -FLT_MAX;
                for (const auto& point : points) {
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
            if (overlap < minOverlap) {
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

    // --- Calcul du point de contact exact ---
    // Trouver les arêtes en collision
    std::vector<Vector2> contactPoints;
    for (size_t i = 0; i < pointsA.size(); i++) {
        Vector2 p1 = pointsA[i];
        Vector2 p2 = pointsA[(i + 1) % pointsA.size()];

        for (size_t j = 0; j < pointsB.size(); j++) {
            Vector2 p3 = pointsB[j];
            Vector2 p4 = pointsB[(j + 1) % pointsB.size()];

            // Calculer l'intersection entre les segments (p1, p2) et (p3, p4)
            Vector2 intersection;
            if (LineSegmentIntersection(p1, p2, p3, p4, intersection)) {
                contactPoints.push_back(intersection);
            }
        }
    }

    // Si aucune intersection n'est trouvée, utiliser le point le plus proche
    if (contactPoints.empty()) {
        Vector2 closestA, closestB;
        float minDistSq = FLT_MAX;
        for (const auto& pA : pointsA) {
            for (const auto& pB : pointsB) {
                float distSq = (pA - pB).LengthSquared();
                if (distSq < minDistSq) {
                    minDistSq = distSq;
                    closestA = pA;
                    closestB = pB;
                }
            }
        }
        outResult.Point = (closestA + closestB) * 0.5f;
    }
    else {
        // Utiliser le premier point d'intersection trouvé
        outResult.Point = contactPoints[0];
    }

    // --- Remplissage des autres données ---
    outResult.Normal = smallestAxis;
    outResult.Penetration = minOverlap;
    outResult.IsColliding = true;
    outResult.ColliderA = const_cast<AABBCollider*>(this);
    outResult.ColliderB = pOther;
    outResult.ActorA = GetOwner();
    outResult.ActorB = pOther->GetOwner();

    return true;
}

bool AABBCollider::LineSegmentIntersection(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& outIntersection) const
{
    float denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    if (denom == 0) return false; // Segments parallèles

    float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
    float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;

    if (ua < 0 || ua > 1 || ub < 0 || ub > 1) return false; // Intersection hors segments

    outIntersection.x = p1.x + ua * (p2.x - p1.x);
    outIntersection.y = p1.y + ua * (p2.y - p1.y);
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
