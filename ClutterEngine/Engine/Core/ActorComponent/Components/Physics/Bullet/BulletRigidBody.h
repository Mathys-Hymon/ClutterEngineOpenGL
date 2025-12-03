#pragma once
#include <Core/ActorComponent/Components/Physics/IRigidbody.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>

namespace clt
{
	
	class CLUTTER_API BulletRigidBody : public IRigidbody
	{
		class BulletPhysics* mWorld;
		btRigidBody* mBody;
		btMotionState* mMotionState;
		btCompoundShape* mShapes;
		
		// Serialized Variables
		
		float mMass;
		rbState mState;
		
		Vector3 mLockPosition{0,0,0}; // 1 = locked, 0 = free
		Vector3 mLockRotation{0,0,0};

	protected:

		void SyncFromBullet();
		void SyncToBullet();

	public:
		CLUTTER_CLASS(BulletRigidBody);
		
		BulletRigidBody(rbState state = rbState::Dynamic, float mass = 1);
		~BulletRigidBody();
		
		void SetupProperties() override 
		{
			CPROPERTY(mState, PropMode::ReadWrite);
          
			CPROPERTY_COND(mMass, PropMode::ReadWrite, this->mState == rbState::Dynamic);

			CPROPERTY(mLockPosition, PropMode::ReadWrite);
			CPROPERTY(mLockRotation, PropMode::ReadWrite);
		}
		
		void SetWorld(class BulletPhysics* world);
		void Start() override;

		virtual void SetState(rbState state) override;
		virtual rbState GetState() override { return mState; };

		void SetMass(float mass) override;
		float GetMass() const override;

		void SetVelocity(const Vector3& vel) override;
		Vector3 GetVelocity() const override;

		virtual void SetCustomGravity(const Vector3& gravity) override;

		void LockRotation(bool x, bool y, bool z) override;
		void LockPosition(bool x, bool y, bool z) override;

		void AddForce(const Vector3& force) override;
		void AddImpulse(const Vector3& impulse) override;

		void AddForceAtLocation(const Vector3& force, const Vector3& relativeLoc) override;
		void AddImpulseAtLocation(const Vector3& impulse, const Vector3& relativeLoc) override;

		void AttachCollider(ICollider* collider) override;
		void RemoveCollider(ICollider* collider) override;
		
		btRigidBody* GetInternalBody() { return mBody; }

		friend BulletPhysics;
	};
}