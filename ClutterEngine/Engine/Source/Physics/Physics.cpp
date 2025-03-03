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
    mColliders2D.push_back(pCollider);
    if (m2DColliderEvent.find(pCollider) == m2DColliderEvent.end())
    {
        m2DColliderEvent[pCollider] = new CollisionEvent();
    }
}

// Adds a rigidbody to the physics engine
void Physics::AddRigidbody(RigidBody2D* pRigidbody)
{
    mRigidbody2D.push_back(pRigidbody);
}

// Removes a rigidbody from the physics engine
void Physics::RemoveRigidBody(RigidBody2D* pRigidbody)
{
    // Implementation needed
}

// Removes a collider from the physics engine
void Physics::RemoveCollider(Collider2DComponent* pCollider)
{
    mColliders2D.erase(std::remove(mColliders2D.begin(), mColliders2D.end(), pCollider), mColliders2D.end());
    if (m2DColliderEvent.find(pCollider) != m2DColliderEvent.end()) {
        delete m2DColliderEvent[pCollider];
        m2DColliderEvent.erase(pCollider);
    }
}

// Subscribes a listener to collision events for a specific collider
void Physics::SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener)
{
    size_t hasCollider = m2DColliderEvent.count(pCollider);

    if (!hasCollider)
    {
        m2DColliderEvent[pCollider] = new CollisionEvent();
    }
    m2DColliderEvent[pCollider]->Subscribe(pListener);
}

// Updates the physics engine, applying gravity and checking for collisions
void Physics::Update()
{
    for (auto& rb : mRigidbody2D)
    {
        if (!rb->mIsKinematic && rb->IsActive())
        {
            rb->AddVelocity(mGravity * rb->GetGravityScale() * Timer::deltaTime);
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
    mCurrentFrameCollisions2D.clear();

    for (size_t i = 0; i < mColliders2D.size(); i++)
    {
        for (size_t j = i + 1; j < mColliders2D.size(); j++)
        {
            Collider2DComponent* a = mColliders2D[i];
            Collider2DComponent* b = mColliders2D[j];
            hitResult2D result;

            if (a->CheckCollision(b, result))
            {
                mCurrentFrameCollisions2D.push_back(result);
            }
        }
    }
}

// Resolves detected collisions by adjusting positions and velocities
void Physics::ResolveCollisions()
{
    // Iterate through all current frame collisions
    for (auto& result : mCurrentFrameCollisions2D)
    {
        // Get the rigid bodies involved in the collision
        RigidBody2D* rbA = result.ActorA->GetComponentOfType<RigidBody2D>();
        RigidBody2D* rbB = result.ActorB->GetComponentOfType<RigidBody2D>();

        float restitution = std::max(result.ColliderA->mBounciness, result.ColliderB->mBounciness);

        // Check if neither collider is a trigger
        if (!result.ColliderA->IsTrigger() && !result.ColliderB->IsTrigger())
        {
            // Calculate the correction vector to resolve penetration
            const Vector2 correction = result.Normal * result.Penetration;
            const float safetyFactor = 1.1f;
            const Vector2 safeCorrection = correction * safetyFactor;

            // Calculate combined friction
            float combinedFriction = result.ColliderA->mFriction * result.ColliderB->mFriction;
            float combinedBounciness = std::max(result.ColliderA->mBounciness, result.ColliderB->mBounciness);

            // Case 1: Only rbA is dynamic
            if (rbA && !rbA->mIsKinematic && rbA->IsActive() && !rbB)
            {
                // Apply position correction to ActorA
                result.ActorA->AddActorLocationOffset(-safeCorrection);

                // Calculate velocity, normal and tangent vectors
                Vector2 velocity = rbA->GetVelocity();
                Vector2 normal = -result.Normal.Normalized();
                Vector2 tangent = Vector2(-normal.y, normal.x).Normalized();

                float velocityAlongNormal = Vector2::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    if (normal.x != 0) velocity.x *= combinedBounciness * normal.x;
                    if (normal.y != 0) velocity.y *= combinedBounciness * normal.y;
                }

                float velocityTangent = Vector2::Dot(velocity, tangent);

                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = (tangent * velocityTangent) + (normal * Vector2::Dot(velocity, normal));

                rbA->SetVelocity(velocity);

                if (!rbA->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector2 contactPoint = result.Point;
                    Vector2 centerA = result.ActorA->GetActorLocation().xy();
                    Vector2 contactOffset = centerA - contactPoint;

                    Vector2 gravityForce = Vector2(0.0f, rbA->mMass * mGravity.y * rbA->mGravityScale);
                    Vector2 reactionForce = -result.Normal * velocityAlongNormal * rbA->mMass * 10.0f;
                    Vector2 totalForce = gravityForce + reactionForce;

                    rbA->mTorque += contactOffset.Cross(totalForce);
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
                Vector2 velocity = rbB->GetVelocity();
                Vector2 normal = result.Normal.Normalized();
                Vector2 tangent = Vector2(-normal.y, normal.x).Normalized();

                float velocityAlongNormal = Vector2::Dot(velocity, normal);

                if (velocityAlongNormal < 0.0f)
                {
                    if (normal.x != 0) velocity.x  = std::abs(velocity.x) * combinedBounciness * normal.x;
                    if (normal.y != 0) velocity.y  = std::abs(velocity.y) * combinedBounciness * normal.y;
                }

                float velocityTangent = Vector2::Dot(velocity, tangent);

                velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
                velocity = (tangent * velocityTangent) + (normal * Vector2::Dot(velocity, normal));

                rbB->SetVelocity(velocity);

                if (!rbB->mLockRotation)
                {
                    // Calculate torque based on collision point
                    Vector2 contactPoint = result.Point;
                    Vector2 centerB = rbB->GetWorldPosition().xy();
                    Vector2 contactOffset = centerB - contactPoint;

                    Vector2 gravityForce = Vector2(0.0f, rbB->mMass * mGravity.y * rbB->mGravityScale);
                    Vector2 reactionForce = result.Normal * velocityAlongNormal * rbB->mMass * 10.0f;
                    Vector2 totalForce = gravityForce + reactionForce;

                    rbB->mTorque += contactOffset.Cross(totalForce);
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
                Vector2 centerA = result.ActorA->GetActorLocation().xy();
                Vector2 centerB = result.ActorB->GetActorLocation().xy();
                Vector2 rA = contactPoint - centerA;
                Vector2 rB = contactPoint - centerB;
                Vector2 force = result.Normal * impulseMagnitude * 5;

                if (rbA && !rbA->mLockRotation)
                {
                    float torqueA = rA.Cross(-force * rbA->mMass);
                    rbA->mTorque += torqueA;
                }

                if (rbB && !rbB->mLockRotation)
                {
                    float torqueB = rB.Cross(force * rbB->mMass);
                    rbB->mTorque += torqueB;
                }
            }
        }
    }
}

// Dispatches collision events to subscribed listeners
void Physics::DispatchEvents()
{
    std::set<std::pair<Collider2DComponent*, Collider2DComponent*>> currentCollisions;

    for (hitResult2D& result : mCurrentFrameCollisions2D)
    {
        auto colliderPair = (result.ColliderA < result.ColliderB)
            ? std::make_pair(result.ColliderA, result.ColliderB)
            : std::make_pair(result.ColliderB, result.ColliderA);

        currentCollisions.insert(colliderPair);
    }

    // ENTER
    for (auto& colliderPair : currentCollisions)
    {
        if (!mPreviousCollisions2D.count(colliderPair))
        {
            for (hitResult2D& result : mCurrentFrameCollisions2D)
            {
                if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
                    (result.ColliderA == colliderPair.second && result.ColliderB == colliderPair.first))
                {
                    if (m2DColliderEvent.count(result.ColliderA))
                    {
                        m2DColliderEvent[result.ColliderA]->NotifyEnter(result);
                    }
                    if (m2DColliderEvent.count(result.ColliderB))
                    {
                        m2DColliderEvent[result.ColliderB]->NotifyEnter(result);
                    }
                    break;
                }
            }
        }
    }

    // STAY
    for (auto& colliderPair : mPreviousCollisions2D)
    {
        if (currentCollisions.count(colliderPair))
        {
            for (hitResult2D& result : mCurrentFrameCollisions2D)
            {
                if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
                    (result.ColliderB == colliderPair.second && result.ColliderB == colliderPair.first))
                {
                    if (m2DColliderEvent.count(result.ColliderA))
                    {
                        m2DColliderEvent[result.ColliderA]->NotifyStay(result);
                    }
                    if (m2DColliderEvent.count(result.ColliderB))
                    {
                        m2DColliderEvent[result.ColliderB]->NotifyStay(result);
                    }
                }
            }
        }
    }

    // EXIT
    for (auto& colliderPair : mPreviousCollisions2D)
    {
        if (!currentCollisions.count(colliderPair))
        {
            for (hitResult2D& prevResult : mPreviousFrameCollisions2D)
            {
                if ((prevResult.ColliderA == colliderPair.first && prevResult.ColliderB == colliderPair.second) ||
                    (prevResult.ColliderA == colliderPair.second && prevResult.ColliderB == colliderPair.first))
                {
                    if (m2DColliderEvent.count(colliderPair.first))
                    {
                        m2DColliderEvent[colliderPair.first]->NotifyExit(prevResult);
                    }
                    if (m2DColliderEvent.count(colliderPair.second))
                    {
                        m2DColliderEvent[colliderPair.second]->NotifyExit(prevResult);
                    }
                }
            }
        }
    }
}
