#pragma once
#include <Physics/IPhysics.h>
#include <Bullet/bullet/btBulletDynamicsCommon.h>

namespace clt
{
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
	    class IRigidbody* CreateRigidbody() override;
	    void DestroyRigidBody(IRigidbody* body) override;
	   
	    class ICollider* CreateCollider() override;
	    void DestroyCollider(ICollider* collider) override;
	   
	    bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, raycastHit& hit, bool debugPersistant = false, Actor* self = nullptr) override;

		btDiscreteDynamicsWorld* GetWorld() { return mDynamicsWorld; }
	};
}