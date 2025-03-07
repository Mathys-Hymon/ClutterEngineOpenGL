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
	mAngularVelocity += (mTorque / mInertia) * deltaTime;
	mTorque = Vector3::Zero;
	mAngularVelocity *= std::pow(0.98f, deltaTime * 60.0f);
	Quaternion rotationDelta = Quaternion::FromEuler(mAngularVelocity * deltaTime);
	mOwner->AddActorRotationOffset(rotationDelta);
}