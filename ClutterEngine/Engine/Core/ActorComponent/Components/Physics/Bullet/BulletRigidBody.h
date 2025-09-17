#pragma once
#include <Core/ActorComponent/Components/Physics/IRigidbody.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>
#include <Physics/Bullet/BulletPhysics.h>

namespace clt
{
	class CLUTTER_API BulletRigidBody : public IRigidbody
	{
		BulletPhysics* mWorld;
		btRigidBody* mBody;
		btMotionState* mMotionState;
		btCollisionShape* mShape;
		float mMass;

	public:
		BulletRigidBody(BulletPhysics* world);
		~BulletRigidBody();

		void SetMass(float mass) override;
		float GetMass() const override;

		void SetVelocity(const Vector3& vel) override;
		Vector3 GetVelocity() const override;

		void ApplyForce(const Vector3& force) override;
		void ApplyImpulse(const Vector3& impulse) override;

		void AttachCollider(ICollider* collider) override;

		btRigidBody* GetInternalBody() { return mBody; }
	};
}