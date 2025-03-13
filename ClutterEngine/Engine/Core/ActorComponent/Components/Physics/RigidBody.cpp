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
    // Calcul de l'accélération angulaire à partir du torque accumulé et de l'inertie
    Vector3 angularAcceleration = mTorque / CalculateInertia();
    mAngularVelocity += angularAcceleration * deltaTime;

    // Appliquer une friction angulaire (air friction) pour réduire progressivement l'angularVelocity.
    // Le coefficient (ici 0.98) peut être ajusté pour avoir l'effet désiré.
    const float dampingCoefficient = 0.98f;
    mAngularVelocity *= std::pow(dampingCoefficient, deltaTime * 60.0f);

    // Si la vitesse angulaire est significative, mettre à jour la rotation
    if (mAngularVelocity.Length() > 0.0001f)
    {
        // Vous pouvez ajuster le facteur (ici deltaTime) pour moduler l'effet de la rotation
        Quaternion deltaRot = Quaternion::FromEuler(mAngularVelocity * deltaTime);
        mOwner->SetActorRotation(Quaternion::Concatenate(deltaRot, mOwner->GetRotation()));
    }

    // Réinitialiser le torque pour le prochain frame
    mTorque = Vector3::Zero;
}

float RigidBody::CalculateInertia() const
{
	const Vector3 size = GetWorldScale();

	return (1.0f / 12.0f) * mMass * (size.x * size.x + size.y * size.y + size.z * size.z);
}
