#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>

using namespace clt;

BulletRigidBody::BulletRigidBody(BulletPhysics* world) :
    mWorld(world), mBody(nullptr), mMotionState(nullptr), mShape(nullptr), mMass(0.0f)
{}

BulletRigidBody::~BulletRigidBody()
{
    if (mBody)
    {
        mWorld->GetWorld()->removeRigidBody(mBody);
        delete mBody;
    }
    delete mMotionState;
    delete mShape;
}

void BulletRigidBody::SetMass(float mass)
{
}

float BulletRigidBody::GetMass() const
{
    return 0.0f;
}

void BulletRigidBody::SetVelocity(const Vector3& vel)
{
}

Vector3 BulletRigidBody::GetVelocity() const
{
    return Vector3();
}

void BulletRigidBody::ApplyForce(const Vector3& force)
{
}

void BulletRigidBody::ApplyImpulse(const Vector3& impulse)
{
}

void BulletRigidBody::AttachCollider(ICollider* collider)
{
}
