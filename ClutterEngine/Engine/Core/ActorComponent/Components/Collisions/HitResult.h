#pragma once
#include <Core/CCommon.h>

namespace clt
{
    class Actor;
    class ColliderComponent;
    struct CLUTTER_API hitResult
    {
        Actor* ActorA = nullptr;
        Actor* ActorB = nullptr;
        ColliderComponent* ColliderA = nullptr;
        ColliderComponent* ColliderB = nullptr;
        Vector3 Point;
        Vector3 Normal;
        float Penetration = 0.0f;
    };
}