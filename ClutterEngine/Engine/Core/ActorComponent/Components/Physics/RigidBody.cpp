#include "pch.h"
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Physics/Iphysics.h>
#include <Core/Timer.h>
#include <Core/Levels/Level.h>

using namespace clt;

RigidBody::RigidBody(float pMass, int pUpdadeOrder) : Component(pUpdadeOrder), mAcceleration(Vector3::Zero), mAngularVelocity(0.0f), mMass(pMass), mVelocity(Vector3::Zero), mGravityScale(1), mInertia(1.0f), mTorque(0.0f), mInvMass((mMass != 0.0f) ? 1.0f / mMass : 0.0f)
{
}

void RigidBody::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	//mOwner->GetLevel()->GetPhysics().AddRigidbody(this);
    CalculateInertia();
}

void RigidBody::ApplyForceAtPoint(const Vector3& force, const Vector3& point)
{
    mForce += force;

    Vector3 r = point - mOwner->GetActorLocation();
    Vector3 torque = Vector3::Cross(r, force);
    mTorque += torque;
}

void RigidBody::ApplyImpulseAtPoint(const Vector3& impulse, const Vector3& point)
{
    AddVelocity(impulse * mInvMass);

    if (mLockRotation) return;

    Vector3 r = point - mOwner->GetActorLocation(); 
    Vector3 angularImpulse = Vector3::Cross(r, impulse * 10);

    AddAngularImpulse(angularImpulse);
}

void RigidBody::AddAngularImpulse(const Vector3& pImpulse)
{
    if (mLockRotation || mInvMass == 0.0f) return;

    mAngularVelocity += pImpulse * mInvInertia;
}

void RigidBody::UpdateRotation(float deltaTime)
{
        Vector3 angularAcceleration = mTorque * mInvInertia;
    mAngularVelocity += angularAcceleration * deltaTime;

    const float dampingCoefficient = 0.98f;
    mAngularVelocity *= std::pow(dampingCoefficient, deltaTime * 60.0f);

    if (mAngularVelocity.Length() > 0.0001f) 
    {
        Quaternion deltaRot = Quaternion::FromEuler(mAngularVelocity * deltaTime);
        mOwner->SetActorRotation(Quaternion::Concatenate(deltaRot, mOwner->GetActorRotation()));
    }

    mTorque = Vector3::Zero;
}

void RigidBody::CalculateInertia()
{
    const Vector3 size = GetWorldScale();

    mInertia.x = (1.0f / 12.0f) * mMass * (size.y * size.y + size.z * size.z);
    mInertia.y = (1.0f / 12.0f) * mMass * (size.x * size.x + size.z * size.z);
    mInertia.z = (1.0f / 12.0f) * mMass * (size.x * size.x + size.y * size.y);

    mInvInertia = Vector3(
        mInertia.x > 0 ? 1.0f / mInertia.x : 0.0f,
        mInertia.y > 0 ? 1.0f / mInertia.y : 0.0f,
        mInertia.z > 0 ? 1.0f / mInertia.z : 0.0f);
}

void RigidBody::ApplyForces(float dt)
{
    if (mMass <= 0.0f || !mOwner || !mSimulatePhysics || mIsKinematic)
    {
        mForce = Vector3::Zero;
        mVelocity = Vector3::Zero;
        return;
    }

    mAcceleration = mForce * mInvMass;
    mVelocity += mAcceleration * dt;

    mOwner->AddActorLocationOffset(mVelocity * dt);

    if (!mLockRotation)
    {
        UpdateRotation(dt);
    }

    mForce = Vector3::Zero;
}
