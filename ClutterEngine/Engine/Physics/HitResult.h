#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector3.h>

namespace clt
{
    class Actor;
    class ColliderComponent;
}

enum class CLUTTER_API TraceChannel : uint16_t
{
    WorldStatic = 1 << 0,
    WorldDynamic = 1 << 1,
    Pawn = 1 << 2,
    Visibility = 1 << 3,
    Camera = 1 << 4,

    All = 0xFFFF
};

struct CLUTTER_API TraceParams
{
    TraceChannel Channel = TraceChannel::Visibility;

    uint16_t CollisionMask = static_cast<uint16_t>(TraceChannel::All);

    clt::Actor* IgnoreActor = nullptr;

    bool IgnoreSelf = true;
    bool DrawDebug = false;
    bool DebugPersistent = false;
};

struct CLUTTER_API HitResult
{
    clt::Actor* ActorA = nullptr;
    clt::Actor* ActorB = nullptr;
    clt::ColliderComponent* ColliderA = nullptr;
    clt::ColliderComponent* ColliderB = nullptr;
    Vector3 Point;
    Vector3 Normal;
    float Penetration = 0.0f;
};

struct CLUTTER_API RaycastHit
{
    bool HitResult = false;
    clt::Actor* Actor = nullptr;
    clt::ColliderComponent* Collider = nullptr;
    Vector3 Point;
    Vector3 Normal;
    float Distance = 0.0f;
};
