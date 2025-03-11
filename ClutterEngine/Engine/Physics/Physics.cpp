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
            const Vector3 correction = result.Normal * result.Penetration;
            const float safetyFactor = 1.1f;
            const Vector3 safeCorrection = correction * safetyFactor;

            // Calculate combined friction
            float combinedFriction = result.ColliderA->mFriction * result.ColliderB->mFriction;
            float combinedBounciness = std::max(result.ColliderA->mBounciness, result.ColliderB->mBounciness);

            // Case 1: Only rbA is dynamic
            if (rbA && !rbA->mIsKinematic && rbA->IsActive() && !rbB)
            {
                // Apply position correction to ActorA
                result.ActorA->AddActorLocationOffset(-safeCorrection);

                // Calculate velocity, normal and tangent vectors
                Vector3 velocity = rbA->GetVelocity();
                Vector3 normal = -result.Normal.Normalized();

                Vector3 arbitrary = (std::abs(normal.x) < 0.9f) ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
                Vector3 tangent = Vector3::Cross(normal, arbitrary).Normalized();

                float velocityAlongNormal = Vector3::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    if (normal.x != 0) velocity.x *= combinedBounciness * normal.x;
                    if (normal.y != 0) velocity.y *= combinedBounciness * normal.y;
                }

                float velocityTangent = Vector3::Dot(velocity, tangent);

                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = (tangent * velocityTangent) + (normal * Vector3::Dot(velocity, normal));

                rbA->SetVelocity(velocity);

                if (!rbA->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector3 contactPoint = result.Point;
                    Vector3 centerA = result.ActorA->GetActorLocation().xy();
                    Vector3 contactOffset = centerA - contactPoint;

                    Vector3 gravityForce = Vector3(0.0f, rbA->mMass * mGravity.y * rbA->mGravityScale, 0.0f);
                    Vector3 reactionForce = -result.Normal * velocityAlongNormal * rbA->mMass * 10.0f;
                    Vector3 totalForce = gravityForce + reactionForce;

                    rbA->mTorque += Vector3::Cross(contactOffset, totalForce);
                }

                // Check if rbA is grounded
                if (-result.Normal.y > 0.5f)
                {
                    rbA->SetVelocity(Vector2(rbA->GetVelocity().x, std::clamp(rbA->GetVelocity().y, 0.0f, FLT_MAX)));
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
                Vector3 arbitrary = (std::abs(normal.x) < 0.9f) ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
                Vector3 tangent = Vector3::Cross(normal, arbitrary).Normalized();

                float velocityAlongNormal = Vector3::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    if (normal.x != 0) velocity.x  = std::abs(velocity.x) * combinedBounciness * normal.x;
                    if (normal.y != 0) velocity.y  = std::abs(velocity.y) * combinedBounciness * normal.y;
                    if (normal.z != 0) velocity.z  = std::abs(velocity.z) * combinedBounciness * normal.z;
                }

                float velocityTangent = Vector3::Dot(velocity, tangent);

                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = (tangent * velocityTangent) + (normal * Vector3::Dot(velocity, normal));

                rbB->SetVelocity(velocity);

                if (!rbB->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector3 contactPoint = result.Point;
                    Vector3 centerB = rbB->GetWorldLocation().xy();
                    Vector3 contactOffset = centerB - contactPoint;

                    Vector3 gravityForce = Vector3(0.0f, rbB->mMass * mGravity.y * rbB->mGravityScale, 0.0f);
                    Vector3 reactionForce = result.Normal * velocityAlongNormal * rbB->mMass * 10.0f;
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
                // Calculate relative velocity and velocity along the normal
                Vector3 relativeVelocity = rbB->GetVelocity() - rbA->GetVelocity();
                float velAlongNormal = Vector3::Dot(relativeVelocity, result.Normal);

                // Calculate impulse magnitude and apply impulse
                const float restitution = 0.5f;
                const float invMassA = 1.0f / rbA->mMass;
                const float invMassB = 1.0f / rbB->mMass;
                const float totalInverseMass = invMassA + invMassB;
                const float impulseMagnitude = -(1 + restitution) * velAlongNormal / totalInverseMass;
                const Vector3 impulse = impulseMagnitude * result.Normal;
                rbA->SetVelocity(rbA->GetVelocity() - impulse * invMassA);
                rbB->SetVelocity(rbB->GetVelocity() + impulse * invMassB);

                // Calculate friction and apply tangent impulse
                const float friction = std::sqrt(result.ColliderA->mFriction * result.ColliderB->mFriction * 0.01f);
                const Vector3 tangent = (relativeVelocity - result.Normal * velAlongNormal).Normalized();
                const float velAlongTangent = Vector3::Dot(relativeVelocity, tangent);
                const float tangentImpulseMagnitude = -velAlongTangent / totalInverseMass * friction;
                const Vector3 tangentImpulse = tangent * tangentImpulseMagnitude;
                rbA->SetVelocity(rbA->GetVelocity() - tangentImpulse * invMassA);
                rbB->SetVelocity(rbB->GetVelocity() + tangentImpulse * invMassB);

                // Apply position correction
                if (totalInverseMass > 0)
                {
                    const Vector3 correctionA = -correction * (invMassA / totalInverseMass);
                    const Vector3 correctionB =  correction * (invMassB / totalInverseMass);
                    result.ActorA->AddActorLocationOffset(correctionA);
                    result.ActorB->AddActorLocationOffset(correctionB);
                    if (rbA->mCanStepOn) rbB->mIsGrounded = true;
                    if (rbB->mCanStepOn) rbA->mIsGrounded = true;
                }

                // Calculate torque based on collision point
                Vector3 contactPoint = result.Point;
                Vector3 centerA = result.ActorA->GetActorLocation().xy();
                Vector3 centerB = result.ActorB->GetActorLocation().xy();
                Vector3 rA = contactPoint - centerA;
                Vector3 rB = contactPoint - centerB;
                Vector3 force = result.Normal * impulseMagnitude * 5;

                if (rbA && !rbA->mLockRotation)
                {
                    Vector3 torqueA = Vector3::Cross(rA, -force * rbA->mMass);
                    rbA->mTorque += torqueA;
                }

                if (rbB && !rbB->mLockRotation)
                {
                    Vector3 torqueB = Vector3::Cross(rB, force * rbB->mMass);
                    rbB->mTorque += torqueB;
                }
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
