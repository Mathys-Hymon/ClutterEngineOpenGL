#include "pch.h"  
#include <Physics/ClutterPhysics.h>  
#include "Core/ActorComponent/Components/Physics/Collisions/OBBCollider.h"
#include "Core/ActorComponent/Components/Physics/Collisions/SphereCollider.h"
#include <Core/Timer.h>  

using namespace clt;

// Constructor initializing gravity vector
ClutterPhysics::ClutterPhysics() : mGravity({ 0.0f, -9.81f, 0.0f })
{
}

bool ClutterPhysics::LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant, Actor* self)
{
    hit.Distance = maxDistance;

    direction = -direction.Normalized();
    Vector3 end = start + direction * maxDistance;

    for (ColliderComponent* collider : mColliders)
    {
        if (!collider->IsActive()) continue;

        Actor* owner = collider->GetOwner();

        if (self && self == owner) continue;

        Transform transform = owner->GetTransform();
        Vector3 position = transform.Location();
        Vector3 scale = transform.Scale();

        if (collider->GetType() == ColliderType::OBB)
        {
            OBBCollider* obb = static_cast<OBBCollider*>(collider);
            Vector3 axes[3];
            obb->GetOBBAxis(axes);
            Vector3 extents = obb->GetBoxExtend() * scale;

            Vector3 localStart = start - position;
            localStart = Vector3(
                Vector3::Dot(localStart, axes[0]),
                Vector3::Dot(localStart, axes[1]),
                Vector3::Dot(localStart, axes[2])
            );

            Vector3 localDir = Vector3(
                Vector3::Dot(direction, axes[0]),
                Vector3::Dot(direction, axes[1]),
                Vector3::Dot(direction, axes[2])
            );

            float tMin = 0.0f;
            float tMax = maxDistance;
            bool hitFound = true;

            for (int axis = 0; axis < 3; axis++)
            {
                if (Maths::Abs(localDir[axis]) < 1e-6f)
                {
                    if (localStart[axis] < -extents[axis] || localStart[axis] > extents[axis])
                    {
                        hitFound = false;
                        break;
                    }
                }
                else
                {
                    float invDir = 1.0f / localDir[axis];
                    float t1 = (-extents[axis] - localStart[axis]) * invDir;
                    float t2 = (extents[axis] - localStart[axis]) * invDir;

                    if (t1 > t2) std::swap(t1, t2);
                    tMin = Maths::Max(tMin, t1);
                    tMax = Maths::Min(tMax, t2);

                    if (tMin > tMax)
                    {
                        hitFound = false;
                        break;
                    }
                }
            }

            if (hitFound && tMin < hit.Distance)
            {
                hit.Distance = tMin;
                hit.Point = start + direction * tMin;
                hit.Actor = owner;
                hit.Collider = collider;
            }
        }

        else if (collider->GetType() == ColliderType::Sphere)
        {
            SphereCollider* sphere = static_cast<SphereCollider*>(collider);
            float radius = sphere->GetRadius() * scale.x;
            Vector3 center = position;

            Vector3 toCenter = center - start;
            float projection = Vector3::Dot(direction, toCenter);
            float distSq = toCenter.LengthSq() - projection * projection;

            if (distSq <= radius * radius)
            {
                float t = projection - Maths::Sqrt(radius * radius - distSq);
                if (t >= 0 && t < hit.Distance)
                {
                    hit.Distance = t;
                    hit.Point = start + direction * t;
                    hit.Normal = (hit.Point - center).Normalized();
                    hit.Actor = owner;
                    hit.Collider = collider;
                }
            }
        }
    }

    if (hit.Actor)
    {
        hit.hitResult = true;
        DebugDraw::Get().DrawLine(start, hit.Point, Color::Red, 3.0f, debugPersistant);
        DebugDraw::Get().DrawLine(hit.Point, end, Color::Green, 3.0f, debugPersistant);

        DebugDraw::Get().DrawBox(hit.Point, 0.05f, Color::Red, 3.0f, Quaternion::FromEuler(hit.Normal), debugPersistant);
    }
    else DebugDraw::Get().DrawLine(start, end, Color::Red, 3.0f, debugPersistant);


    return hit.hitResult;
}

// Adds a collider to the physics engine
void ClutterPhysics::AddCollider(ColliderComponent* pCollider)
{
    mColliders.push_back(pCollider);
    if (mColliderEvent.find(pCollider) == mColliderEvent.end())
    {
        mColliderEvent[pCollider] = new CollisionEvent();
    }
}

// Adds a rigidbody to the physics engine
void ClutterPhysics::AddRigidbody(RigidBody* pRigidbody)
{
    mRigidbody.push_back(pRigidbody);
}

// Removes a rigidbody from the physics engine
void ClutterPhysics::RemoveRigidBody(RigidBody* pRigidbody)
{
    auto it = std::find(mRigidbody.begin(), mRigidbody.end(), pRigidbody);

    if (it != mRigidbody.end())
    {
        mRigidbody.erase(it);
        pRigidbody = nullptr;
    }
}

// Removes a collider from the physics engine
void ClutterPhysics::RemoveCollider(ColliderComponent* pCollider)
{
    if (mColliderEvent.find(pCollider) != mColliderEvent.end())
    {
        delete mColliderEvent[pCollider];
        mColliderEvent.erase(pCollider);
    }

    auto it = std::find(mColliders.begin(), mColliders.end(), pCollider);

    if (it != mColliders.end())
    {
        mColliders.erase(it);
    }
}

// Subscribes a listener to collision events for a specific collider
void ClutterPhysics::SubscribeTo(ColliderComponent* pCollider, ICollisionListener* pListener)
{
    size_t hasCollider = mColliderEvent.count(pCollider);

    if (!hasCollider)
    {
        mColliderEvent[pCollider] = new CollisionEvent();
    }
    mColliderEvent[pCollider]->Subscribe(pListener);
}

// Updates the physics engine, applying gravity and checking for collisions
void ClutterPhysics::Update()
{
    float dt = Timer::clampedDeltaTime;

    for (auto& rb : mRigidbody)
    {
        if (rb->IsActive())
        {
            rb->AddForce(mGravity * rb->GetGravityScale() * rb->GetMass());
            rb->ApplyForces(dt);

            rb->SetGrounded(false);
        }
    }

    CheckCollisions();
    ResolveCollisions();
    DispatchEvents();
}

// Checks for collisions between all colliders
void ClutterPhysics::CheckCollisions()
{
    mCurrentFrameCollisions.clear();

    for (size_t i = 0; i < mColliders.size(); i++)
    {
        for (size_t j = i + 1; j < mColliders.size(); j++)
        {
            ColliderComponent* a = mColliders[i];
            ColliderComponent* b = mColliders[j];
            hitResult result;

            if (a->CheckCollision(b, result))
            {
                mCurrentFrameCollisions.push_back(result);
            }
        }
    }
}

// Resolves detected collisions by adjusting positions and velocities
void ClutterPhysics::ResolveCollisions()
{
    // Iterate through all current frame collisions
    for (auto& hit : mCurrentFrameCollisions)
    {
        if (!hit.ColliderA || !hit.ColliderB) return;

        RigidBody* rbA = hit.ActorA->GetComponentOfType<clt::RigidBody>();
        RigidBody* rbB = hit.ActorB->GetComponentOfType<clt::RigidBody>();

        if (!rbA && !rbB) return;

        const Vector3& normal = hit.Normal;
        float penetration = hit.Penetration;

        const float totalMass = (rbA ? rbA->GetMass() : 0.0f) + (rbB ? rbB->GetMass() : 0.0f);
        if (penetration > 0.0f && totalMass > 0.0f)
        {
            Vector3 correction = normal * (penetration / totalMass) * 0.8f;

            if (rbA) rbA->GetOwner()->AddActorLocationOffset(-correction * (rbA->GetMass() / totalMass));
            if (rbB) rbB->GetOwner()->AddActorLocationOffset(correction * (rbB->GetMass() / totalMass));
        }

        Vector3 velA = rbA ? rbA->GetVelocity() : Vector3::Zero;
        Vector3 velB = rbB ? rbB->GetVelocity() : Vector3::Zero;
        Vector3 relativeVel = velB - velA;

        float velAlongNormal = Vector3::Dot(relativeVel, normal);

        if (velAlongNormal > 0.0f) return;

        float restitution = 0.5f * (hit.ColliderA->mBounciness + hit.ColliderB->mBounciness);

        float invMassA = rbA ? rbA->GetInvMass() : 0;
        float invMassB = rbB ? rbB->GetInvMass() : 0;

        float  impulseScalar = -(1 + restitution) * velAlongNormal / (invMassA + invMassB);
        Vector3 impulse = impulseScalar * normal;

        if (rbA) rbA->ApplyImpulseAtPoint(-impulse, hit.Point);
        if (rbB) rbB->ApplyImpulseAtPoint(impulse, hit.Point);

        Vector3 tangent = relativeVel - normal * Vector3::Dot(relativeVel, normal);
        if (tangent.LengthSq() > 0.0001f)
        {
            tangent.Normalize();

            float frictionCoefficient = 0.5f * (hit.ColliderA->mFriction + hit.ColliderB->mFriction);

            float jt = -Vector3::Dot(relativeVel, tangent);
            jt /= invMassA + invMassB;

            Vector3 frictionImpulse;
            if (std::abs(jt) < impulseScalar * frictionCoefficient)
            {
                // Static friction
                frictionImpulse = jt * tangent;
            }
            else
            {
                // Dynamic friction
                frictionImpulse = -impulseScalar * frictionCoefficient * tangent;
            }

            if (rbA) rbA->ApplyImpulseAtPoint(-frictionImpulse, hit.Point);
            if (rbB) rbB->ApplyImpulseAtPoint(frictionImpulse, hit.Point);
        }

        // ---- Ground check logic  ----

        const float groundThreshold = -0.5f;

        if (rbA && normal.y < groundThreshold && (!rbB || !rbB->IsActive() || rbB->IsGrounded()))
        {
            rbA->SetGrounded(true);
        }

        if (rbB && normal.y < -groundThreshold && (!rbA || !rbA->IsActive() ||rbA->IsGrounded()))
        {
            rbB->SetGrounded(true);
        }
    }
}

// Dispatches collision events to subscribed listeners
void ClutterPhysics::DispatchEvents()
{
    std::set<std::pair<ColliderComponent*, ColliderComponent*>> currentCollisions;

    for (hitResult& result : mCurrentFrameCollisions)
    {
        auto colliderPair = (result.ColliderA < result.ColliderB)
            ? std::make_pair(result.ColliderA, result.ColliderB)
            : std::make_pair(result.ColliderB, result.ColliderA);

        currentCollisions.insert(colliderPair);
    }

    // ENTER
    for (auto& colliderPair : currentCollisions)
    {
        if (!mPreviousCollisions.count(colliderPair))
        {
            for (hitResult& result : mCurrentFrameCollisions)
            {
                if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
                    (result.ColliderA == colliderPair.second && result.ColliderB == colliderPair.first))
                {
                    if (mColliderEvent.count(result.ColliderA))
                    {
                        if (result.ColliderA->IsTrigger())
                        {
                            mColliderEvent[result.ColliderA]->TriggerEnter(result.ColliderA, result);
                        }
                        else  mColliderEvent[result.ColliderA]->NotifyEnter(result.ColliderA, result);
                    }
                    if (mColliderEvent.count(result.ColliderB))
                    {
                        if (result.ColliderB->IsTrigger())
                        {
                            mColliderEvent[result.ColliderB]->TriggerEnter(result.ColliderB, result);
                        }
                        else  mColliderEvent[result.ColliderB]->NotifyEnter(result.ColliderB, result);
                    }
                }
            }
        }
    }

    // STAY
    for (auto& colliderPair : mPreviousCollisions)
    {
        if (currentCollisions.count(colliderPair))
        {
            for (hitResult& result : mCurrentFrameCollisions)
            {
                if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
                    (result.ColliderB == colliderPair.second && result.ColliderB == colliderPair.first))
                {
                    if (mColliderEvent.count(result.ColliderA))
                    {
                        if (result.ColliderA->IsTrigger())
                        {
                            mColliderEvent[result.ColliderA]->TriggerStay(result.ColliderA, result);
                        }
                        else  mColliderEvent[result.ColliderA]->NotifyStay(result.ColliderA, result);
                    }
                    if (mColliderEvent.count(result.ColliderB))
                    {
                        if (result.ColliderB->IsTrigger())
                        {
                            mColliderEvent[result.ColliderB]->TriggerStay(result.ColliderB, result);
                        }
                        else  mColliderEvent[result.ColliderB]->NotifyStay(result.ColliderB, result);
                    }
                }
            }
        }
    }

    // EXIT
    for (auto& colliderPair : mPreviousCollisions)
    {
        if (!currentCollisions.count(colliderPair))
        {
            for (hitResult& prevResult : mPreviousFrameCollisions)
            {
                if ((prevResult.ColliderA == colliderPair.first && prevResult.ColliderB == colliderPair.second) ||
                    (prevResult.ColliderA == colliderPair.second && prevResult.ColliderB == colliderPair.first))
                {
                    if (mColliderEvent.count(prevResult.ColliderA))
                    {
                        if (prevResult.ColliderA->IsTrigger())
                        {
                            mColliderEvent[prevResult.ColliderA]->TriggerExit(prevResult.ColliderA, prevResult);
                        }
                        else  mColliderEvent[prevResult.ColliderA]->NotifyExit(prevResult.ColliderA, prevResult);
                    }
                    if (mColliderEvent.count(prevResult.ColliderB))
                    {
                        if (prevResult.ColliderB->IsTrigger())
                        {
                            mColliderEvent[prevResult.ColliderB]->TriggerExit(prevResult.ColliderB, prevResult);
                        }
                        else  mColliderEvent[prevResult.ColliderB]->NotifyExit(prevResult.ColliderB, prevResult);
                    }
                }
            }
        }
    }

    mPreviousCollisions = currentCollisions;
}
