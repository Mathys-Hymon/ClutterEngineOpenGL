#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	class RigidBody2D : public Component
	{
		Vector2 mVelocity	  = Vector2::ZERO;
		Vector2 mAcceleration = Vector2::ZERO;
		Vector2 mGravity;

	public:
		float mMass = 1.0f;
		bool mSimulatePhysics = false;
		bool mIsKinematic = false;

		void AddForce(const Vector2 pForce) { mAcceleration += (pForce / mMass); };
		void SetVelociy(Vector2 const pVelocity) { mVelocity = pVelocity; };
	};
}