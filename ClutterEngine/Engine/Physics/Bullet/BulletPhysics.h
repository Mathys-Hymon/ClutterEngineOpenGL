#pragma once
#include <Physics/IPhysics.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>

namespace clt
{
	class BulletRigidBody;
	class CLUTTER_API BulletPhysics : public IPhysics
	{
		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfig;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mDynamicsWorld;

		std::vector<BulletRigidBody*> mRigidbodies;

	public:

		BulletPhysics();
		~BulletPhysics();

		void UpdatePhysics() override;
	    void AddRigidbody(IRigidbody*) override;
	    void RemoveRigidBody(IRigidbody* body) override;
	   
	    bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params, Actor* self) override;

		btDiscreteDynamicsWorld* GetWorld() { return mDynamicsWorld; }
	};
}