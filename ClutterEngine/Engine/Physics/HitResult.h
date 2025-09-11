#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector3.h>

namespace clt
{
    class Actor;
    class ColliderComponent;
}

    struct CLUTTER_API hitResult
    {
        clt::Actor* ActorA = nullptr;
        clt::Actor* ActorB = nullptr;
        clt::ColliderComponent* ColliderA = nullptr;
        clt::ColliderComponent* ColliderB = nullptr;
        Vector3 Point;
        Vector3 Normal;
        float Penetration = 0.0f;
    };

    struct CLUTTER_API raycastHit
    {
        bool hitResult = false;
        clt::Actor* Actor = nullptr;
        clt::ColliderComponent* Collider = nullptr;
        Vector3 Point;
        Vector3 Normal;
        float Distance = 0.0f;
    };
