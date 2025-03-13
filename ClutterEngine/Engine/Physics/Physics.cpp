#include "pch.h"  
#include <Physics/Physics.h>  
#include <Core/Timer.h>  

using namespace clt;

// Constructor initializing gravity vector
Physics::Physics() : mGravity({ 0.0f, -300.0f, 0.0f })
{
}

// Destructor
Physics::~Physics()
{
}

// Adds a collider to the physics engine
void Physics::AddCollider(ColliderComponent* pCollider)
{
    mColliders.push_back(pCollider);
    if (mColliderEvent.find(pCollider) == mColliderEvent.end())
    {
        mColliderEvent[pCollider] = new CollisionEvent();
    }
}

// Adds a rigidbody to the physics engine
void Physics::AddRigidbody(RigidBody* pRigidbody)
{
    mRigidbody.push_back(pRigidbody);
}

// Removes a rigidbody from the physics engine
void Physics::RemoveRigidBody(RigidBody* pRigidbody)
{
    // Implementation needed
}

// Removes a collider from the physics engine
void Physics::RemoveCollider(ColliderComponent* pCollider)
{
    mColliders.erase(std::remove(mColliders.begin(), mColliders.end(), pCollider), mColliders.end());
    if (mColliderEvent.find(pCollider) != mColliderEvent.end()) {
        delete mColliderEvent[pCollider];
        mColliderEvent.erase(pCollider);
    }
}

// Subscribes a listener to collision events for a specific collider
void Physics::SubscribeTo(ColliderComponent* pCollider, ICollisionListener* pListener)
{
    size_t hasCollider = mColliderEvent.count(pCollider);

    if (!hasCollider)
    {
        mColliderEvent[pCollider] = new CollisionEvent();
    }
    mColliderEvent[pCollider]->Subscribe(pListener);
}

// Updates the physics engine, applying gravity and checking for collisions
void Physics::Update()
{
    for (auto& rb : mRigidbody)
    {
        if (!rb->mIsKinematic && rb->IsActive())
        {
            if(!rb->mIsGrounded) rb->AddVelocity(mGravity * rb->GetGravityScale() * Timer::deltaTime);

            rb->GetOwner()->AddActorLocationOffset(rb->GetVelocity() * Timer::deltaTime);

            if(!rb->mLockRotation) rb->UpdateRotation(Timer::deltaTime);
            rb->mIsGrounded = false;
        }
    }

    CheckCollisions();
    ResolveCollisions();
    DispatchEvents();
}

// Checks for collisions between all colliders
void Physics::CheckCollisions()
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
void Physics::ResolveCollisions()
{
    // Iterate through all current frame collisions
    for (auto& result : mCurrentFrameCollisions)
    {
        // Get the rigid bodies involved in the collision
        RigidBody* rbA = result.ActorA->GetComponentOfType<RigidBody>();
        RigidBody* rbB = result.ActorB->GetComponentOfType<RigidBody>();

        float restitution = std::max(result.ColliderA->mBounciness, result.ColliderB->mBounciness);

        // Check if neither collider is a trigger
        if (!result.ColliderA->IsTrigger() && !result.ColliderB->IsTrigger())
        {
            // Calculate the correction vector to resolve penetration

            const Vector3 safeCorrection = (result.Normal * result.Penetration) * 50;

            // Calculate combined friction
            float combinedFriction = result.ColliderA->mFriction * result.ColliderB->mFriction;

            // Case 1: Only rbA is dynamic
            if (rbA && !rbA->mIsKinematic && rbA->IsActive() && !rbB)
            {
                // Apply position correction to ActorA
                result.ActorA->AddActorLocationOffset(-safeCorrection);

                // Calculate velocity, normal and tangent vectors
                Vector3 velocity = rbA->GetVelocity();
                Vector3 normal = -result.Normal.Normalized();

                float velocityAlongNormal = Vector3::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    velocity = velocity - (1.0f + restitution) * velocityAlongNormal * normal;
                }

                Vector3 tangent = (velocity - normal * velocityAlongNormal).Normalized();
                float velocityTangent = Vector3::Dot(velocity, tangent);
                velocity = tangent * velocityTangent + normal * velocityAlongNormal;

                rbA->SetVelocity(velocity);

                if (!rbA->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector3 contactPoint = result.Point;
                    Vector3 centerA = result.ActorA->GetActorLocation();
                    Vector3 r = contactPoint - centerA;
                    Vector3 force = normal * velocityAlongNormal * rbA->mMass;
                    rbA->mTorque += Vector3::Cross(r, force);
                }

                // Check if rbA is grounded
                if (-result.Normal.y > 0.5f )
                {
                    rbA->SetVelocity(
                        Vector3(rbA->GetVelocity().x, std::clamp(rbA->GetVelocity().y, 0.0f, FLT_MAX), rbA->GetVelocity().z)
                    );
                    rbA->mIsGrounded = true;
                    rbA->mAngularVelocity *= 0.2f;
                }
            }

            // Case 2: Only rbB is dynamic
            else if (!rbA && rbB && !rbB->mIsKinematic && rbB->IsActive())
            {
                // Apply position correction to ActorB
                result.ActorB->AddActorLocationOffset(safeCorrection);

                // Calculate velocity, normal and tangent vectors
                Vector3 velocity = rbB->GetVelocity();
                Vector3 normal = result.Normal.Normalized();

                float velocityAlongNormal = Vector3::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    velocity = velocity - (1.0f + restitution) * velocityAlongNormal * normal;
                }

                Vector3 tangent = (velocity - normal * velocityAlongNormal).Normalized();
                float velocityTangent = Vector3::Dot(velocity, tangent);
                velocity = tangent * velocityTangent + normal * velocityAlongNormal;

                rbB->SetVelocity(velocity);

                if (!rbB->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector3 contactPoint = result.Point;
                    Vector3 centerB = rbB->GetWorldLocation();
                    Vector3 contactOffset = centerB - contactPoint;
                    Vector3 gravityForce = Vector3(0.0f, rbB->mMass * mGravity.y * rbB->mGravityScale, 0.0f);
                    Vector3 reactionForce = normal * velocityAlongNormal * rbB->mMass * 10.0f;
                    Vector3 totalForce = gravityForce + reactionForce;

                    rbB->mTorque += Vector3::Cross(contactOffset, totalForce);
                }

                // Check if rbB is grounded
                if (result.Normal.y > 0.5f)
                {
                    rbB->SetVelocity(Vector2(rbB->GetVelocity().x, std::clamp(rbB->GetVelocity().y, 0.0f, 10000.0f)));
                    rbB->mIsGrounded = true;
                    rbB->mAngularVelocity *= 0.2f;
                }
            }

            // Case 3: Both rbA and rbB are dynamic
            else if (rbA && rbB && !rbA->mIsKinematic && !rbB->mIsKinematic)
            {
                // --- 1. Calculate relative velocity ---
                Vector3 relativeVelocity = rbB->GetVelocity() - rbA->GetVelocity();
                float velAlongNormal = Vector3::Dot(relativeVelocity, result.Normal);

                // --- 2. Skip if objects are moving apart ---
                if (velAlongNormal > 0) return;

                // --- 3. Calculate normal impulse using conservation laws ---
                const float invMassA = 1.0f / rbA->mMass;
                const float invMassB = 1.0f / rbB->mMass;
                const float totalInverseMass = invMassA + invMassB;
                if (totalInverseMass <= 0) return;

                // Normal impulse magnitude (physics-based collision response)
                const float impulseMagnitude = -(1 + restitution) * velAlongNormal / totalInverseMass;
                const Vector3 impulse = impulseMagnitude * result.Normal;

                // --- 4. Apply impulse to both bodies ---
                rbA->AddVelocity(-impulse * invMassA);
                rbB->AddVelocity( impulse * invMassB);

                // --- 5. Tangential friction impulse ---
                Vector3 tangent = (relativeVelocity - result.Normal * velAlongNormal).Normalized();
                float velAlongTangent = Vector3::Dot(relativeVelocity, tangent);
                float tangentImpulseMagnitude = -velAlongTangent * combinedFriction / totalInverseMass;
                Vector3 tangentImpulse = tangent * tangentImpulseMagnitude;

                rbA->AddVelocity(-tangentImpulse * invMassA);
                rbB->AddVelocity( tangentImpulse * invMassB);

                // --- 6. Position correction to resolve penetration ---
                const float safetyMargin = 0.01f;
                const Vector3 correction = result.Normal * (result.Penetration + safetyMargin) / totalInverseMass;
                result.ActorA->AddActorLocationOffset(-correction * invMassA);
                result.ActorB->AddActorLocationOffset(correction * invMassB);

                // --- 7. torque calculation ---
                Vector3 contactPoint = result.Point;
                Vector3 rA = contactPoint - result.ActorA->GetActorLocation(); // Vector from center to contact point
                Vector3 rB = contactPoint - result.ActorB->GetActorLocation();

                // Torque from normal impulse
                Vector3 torqueA = Vector3::Cross(rA, -impulse);
                Vector3 torqueB = Vector3::Cross(rB,  impulse);

                // Torque from friction impulse
                Vector3 frictionTorqueA = Vector3::Cross(rA, -tangentImpulse);
                Vector3 frictionTorqueB = Vector3::Cross(rB,  tangentImpulse);

                if (!rbA->mLockRotation) rbA->mTorque += torqueA + frictionTorqueA;
                if (!rbB->mLockRotation) rbB->mTorque += torqueB + frictionTorqueB;
            }
        }
    }
}

// Dispatches collision events to subscribed listeners
void Physics::DispatchEvents()
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
                        mColliderEvent[result.ColliderA]->NotifyEnter(result);
                    }
                    if (mColliderEvent.count(result.ColliderB))
                    {
                        mColliderEvent[result.ColliderB]->NotifyEnter(result);
                    }
                    break;
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
                        mColliderEvent[result.ColliderA]->NotifyStay(result);
                    }
                    if (mColliderEvent.count(result.ColliderB))
                    {
                        mColliderEvent[result.ColliderB]->NotifyStay(result);
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
                    if (mColliderEvent.count(colliderPair.first))
                    {
                        mColliderEvent[colliderPair.first]->NotifyExit(prevResult);
                    }
                    if (mColliderEvent.count(colliderPair.second))
                    {
                        mColliderEvent[colliderPair.second]->NotifyExit(prevResult);
                    }
                }
            }
        }
    }
}
