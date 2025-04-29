#include "pch.h"
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Physics/Physics.h>
#include <Core/Timer.h>
#include <Core/Levels/Level.h>

using namespace clt;

RigidBody::RigidBody(float pMass, int pUpdadeOrder) : Component(pUpdadeOrder), mAcceleration(Vector3::Zero), mAngularVelocity(0.0f), mMass(pMass), mVelocity(Vector3::Zero), mGravityScale(1), mInertia(1.0f), mTorque(0.0f)
{}

void RigidBody::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mOwner->GetLevel()->GetPhysics().AddRigidbody(this);
}

void RigidBody::AddForce(const Vector3& pForce)
{
	if (!mIsKinematic && mSimulatePhysics)
	{
		mVelocity += pForce / mMass;
	}
}

void RigidBody::UpdateRotation(float deltaTime)
{
    Vector3 angularAcceleration = mTorque / CalculateInertia();
    mAngularVelocity += angularAcceleration * deltaTime;

    const float dampingCoefficient = 0.98f;
    mAngularVelocity *= std::pow(dampingCoefficient, deltaTime * 60.0f);

    if (mAngularVelocity.Length() > 0.0001f)
    {
        Quaternion deltaRot = Quaternion::FromEuler(mAngularVelocity * deltaTime);
        mOwner->SetActorRotation(Quaternion::Concatenate(deltaRot, mOwner->GetRotation()));
    }
    mTorque = Vector3::Zero;
}

float RigidBody::CalculateInertia() const
{
	const Vector3 size = GetWorldScale();

	return (1.0f / 12.0f) * mMass * (size.x * size.x + size.y * size.y + size.z * size.z);
}
