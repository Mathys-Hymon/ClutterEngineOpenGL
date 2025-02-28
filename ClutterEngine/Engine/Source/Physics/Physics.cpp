#include "pch.h"  
#include <Physics/Physics.h>  
#include <Core/Timer.h>  

using namespace clt;

// Constructor initializing gravity vector
Physics::Physics() : mGravity({ 0.0f, -300.0f })
{
}

// Destructor
Physics::~Physics()
{
}

// Adds a collider to the physics engine
void Physics::AddCollider(Collider2DComponent* pCollider)
{
    mColliders.push_back(pCollider);
    if (mColliderEvent.find(pCollider) == mColliderEvent.end())
    {
        mColliderEvent[pCollider] = new CollisionEvent();
    }
}

// Adds a rigidbody to the physics engine
void Physics::AddRigidbody(RigidBody2D* pRigidbody)
{
    mRigidbody.push_back(pRigidbody);
}

// Removes a rigidbody from the physics engine
void Physics::RemoveRigidBody(RigidBody2D* pRigidbody)
{
    // Implementation needed
}

// Removes a collider from the physics engine
void Physics::RemoveCollider(Collider2DComponent* pCollider)
{
    mColliders.erase(std::remove(mColliders.begin(), mColliders.end(), pCollider), mColliders.end());
    if (mColliderEvent.find(pCollider) != mColliderEvent.end()) {
        delete mColliderEvent[pCollider];
        mColliderEvent.erase(pCollider);
    }
}

// Subscribes a listener to collision events for a specific collider
void Physics::SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener)
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
        rb->mIsGrounded = false;

        if (!rb->mIsKinematic && rb->IsActive())
        {
            rb->AddVelocity(mGravity * rb->GetGravityScale() * Timer::deltaTime);
            rb->UpdateRotation(Timer::deltaTime);
        }

        rb->GetOwner()->AddActorLocationOffset(rb->GetVelocity() * Timer::deltaTime);
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
            Collider2DComponent* a = mColliders[i];
            Collider2DComponent* b = mColliders[j];
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
        RigidBody2D* rbA = result.ActorA->GetComponentOfType<RigidBody2D>();
        RigidBody2D* rbB = result.ActorB->GetComponentOfType<RigidBody2D>();

        // Check if neither collider is a trigger
        if (!result.ColliderA->IsTrigger() && !result.ColliderB->IsTrigger())
        {
            // Calculate the correction vector to resolve penetration
            const Vector2 correction = result.Normal * result.Penetration;
            const float safetyFactor = 1.1f;
            const Vector2 safeCorrection = correction * safetyFactor;

            // Case 1: Only rbA is dynamic
            if (rbA && !rbA->mIsKinematic && rbA->IsActive() && !rbB)
            {
                // Apply position correction to ActorA
                result.ActorA->AddActorLocationOffset(safeCorrection);

                // Calculate combined friction
                float combinedFriction = result.ColliderA->mFriction * result.ColliderB->mFriction;

                // Calculate normal and tangent vectors
                Vector2 normal = result.Normal.Normalized();
                Vector2 tangent = Vector2(normal.y, -normal.x).Normalized();

                // Adjust velocity based on friction
                Vector2 velocity = rbA->GetVelocity();
                float velocityNormal = Vector2::Dot(velocity, normal);
                float velocityTangent = Vector2::Dot(velocity, tangent);
                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = normal * velocityNormal + tangent * velocityTangent;
                rbA->SetVelocity(velocity);

                // Calculate torque based on collision point
                Vector2 contactPoint = result.Point;
                Vector2 centerA = result.ActorA->GetActorLocation();
                Vector2 contactOffset = centerA - contactPoint;
                Vector2 force = result.Normal * velocityNormal * rbA->mMass * 5;
                rbA->mTorque += contactOffset.Cross(force);

                // Check if rbA is grounded
                if (result.Normal.y > 0.5f)
                {
                    rbA->SetVelocity(Vector2(rbA->GetVelocity().x, 0.0f));
                    rbA->mIsGrounded = true;
                    rbA->mAngularVelocity *= 0.2f;
                }
            }
            // Case 2: Only rbB is dynamic
            else if (!rbA && rbB && !rbB->mIsKinematic && rbB->IsActive())
            {
                // Apply position correction to ActorB
                result.ActorB->AddActorLocationOffset(safeCorrection);

                // Calculate combined friction
                float combinedFriction = result.ColliderB->mFriction * result.ColliderA->mFriction;

                // Calculate normal and tangent vectors
                Vector2 normal = result.Normal.Normalized();
                Vector2 tangent = Vector2(normal.y, -normal.x).Normalized();

                // Adjust velocity based on friction
                Vector2 velocity = rbB->GetVelocity();
                float velocityNormal = Vector2::Dot(velocity, normal);
                float velocityTangent = Vector2::Dot(velocity, tangent);
                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = normal * velocityNormal + tangent * velocityTangent;
                rbB->SetVelocity(velocity);

                // Calculate torque based on collision point
                Vector2 contactPoint = result.Point;
                Vector2 centerB = rbB->GetWorldPosition();
                Vector2 contactOffset = centerB - contactPoint;
                Vector2 force = result.Normal * velocityNormal * rbB->mMass * 5;
                rbB->mTorque += contactOffset.Cross(force);

                // Check if rbB is grounded
                if (result.Normal.y > 0.5f)
                {
                    rbB->SetVelocity(Vector2(rbB->GetVelocity().x, 0.0f));
                    rbB->mIsGrounded = true;
                    rbB->mAngularVelocity *= 0.2f;
                }
            }
            // Case 3: Both rbA and rbB are dynamic
            else if (rbA && rbB && !rbA->mIsKinematic && !rbB->mIsKinematic)
            {
                // Calculate relative velocity and velocity along the normal
                Vector2 relativeVelocity = rbB->GetVelocity() - rbA->GetVelocity();
                float velAlongNormal = Vector2::Dot(relativeVelocity, result.Normal);

                // Calculate impulse magnitude and apply impulse
                const float restitution = 0.5f;
                const float invMassA = 1.0f / rbA->mMass;
                const float invMassB = 1.0f / rbB->mMass;
                const float totalInverseMass = invMassA + invMassB;
                const float impulseMagnitude = -(1 + restitution) * velAlongNormal / totalInverseMass;
                const Vector2 impulse = impulseMagnitude * result.Normal;
                rbA->SetVelocity(rbA->GetVelocity() - impulse * invMassA);
                rbB->SetVelocity(rbB->GetVelocity() + impulse * invMassB);

                // Calculate friction and apply tangent impulse
                const float friction = std::sqrt(result.ColliderA->mFriction * result.ColliderB->mFriction * 0.01f);
                const Vector2 tangent = (relativeVelocity - result.Normal * velAlongNormal).Normalized();
                const float velAlongTangent = Vector2::Dot(relativeVelocity, tangent);
                const float tangentImpulseMagnitude = -velAlongTangent / totalInverseMass * friction;
                const Vector2 tangentImpulse = tangent * tangentImpulseMagnitude;
                rbA->SetVelocity(rbA->GetVelocity() - tangentImpulse * invMassA);
                rbB->SetVelocity(rbB->GetVelocity() + tangentImpulse * invMassB);

                // Apply position correction
                if (totalInverseMass > 0)
                {
                    const Vector2 correctionA = -correction * (invMassA / totalInverseMass);
                    const Vector2 correctionB = correction * (invMassB / totalInverseMass);
                    result.ActorA->AddActorLocationOffset(correctionA);
                    result.ActorB->AddActorLocationOffset(correctionB);
                    if (rbA->mCanStepOn) rbB->mIsGrounded = true;
                    if (rbB->mCanStepOn) rbA->mIsGrounded = true;
                }

                // Calculate torque based on collision point
                Vector2 contactPoint = result.Point;
                Vector2 centerA = result.ActorA->GetActorLocation();
                Vector2 centerB = result.ActorB->GetActorLocation();
                Vector2 rA = contactPoint - centerA;
                Vector2 rB = contactPoint - centerB;
                Vector2 force = result.Normal * impulseMagnitude * 5;
                float torqueA = rA.Cross(-force * rbA->mMass);
                float torqueB = rB.Cross(force * rbB->mMass);
                if (rbA) rbA->mTorque += torqueA;
                if (rbB) rbB->mTorque += torqueB;
            }
        }
    }
}

// Dispatches collision events to subscribed listeners
void Physics::DispatchEvents()
{
    std::set<std::pair<Collider2DComponent*, Collider2DComponent*>> currentCollisions;

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
