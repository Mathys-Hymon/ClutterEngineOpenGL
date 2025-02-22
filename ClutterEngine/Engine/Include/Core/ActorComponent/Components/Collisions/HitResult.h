#pragma once
#include <Core/CCommon.h>

namespace clt
{
    class Actor;
    class Collider2DComponent;
    struct CLUTTER_API hitResult
    {
        bool IsColliding = false;
        Actor* ActorA = nullptr;
        Actor* ActorB = nullptr;
        Collider2DComponent* ColliderA = nullptr;
        Collider2DComponent* ColliderB = nullptr;
        Vector2 Point;
        Vector2 Normal;
        float Penetration = 0.0f;
    };
}
