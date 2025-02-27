#include "pch.h"
#include <Core/ActorComponent/Components/Physics/RigidBody2D.h>
#include <Physics/Physics.h>
#include <Core/Levels/Level.h>

using namespace clt;

RigidBody2D::RigidBody2D(float pMass, int pUpdadeOrder) : Component(pUpdadeOrder), mAcceleration(Vector2::Zero), mAngularVelocity(0.0f), mMass(pMass), mVelocity(Vector2::Zero), mGravityScale(1), mGroundFriction(0.5f), mAirFriction(0.1f)
{}

void RigidBody2D::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mOwner->GetLevel()->GetPhysics().AddRigidbody(this);
}

void RigidBody2D::AddForce(const Vector2& pForce)
{
	if (!mIsKinematic && mSimulatePhysics)
	{
		mVelocity += pForce / mMass;
	}
}