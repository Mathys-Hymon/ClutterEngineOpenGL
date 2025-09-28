#pragma once
#include <Physics/IPhysics.h>
#include <Graphics/IRenderer.h>
#include <Core/Debug/BulletDebugDraw.h>
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

		BulletDebugDraw* mDebug;
		CEngine& mEngine;

		std::vector<BulletRigidBody*> mRigidbodies;

	public:

		BulletPhysics(CEngine& engine);
		~BulletPhysics();

		void UpdatePhysics() override;
		void DrawDebug() override;

	    void AddRigidbody(IRigidbody*) override;
	    void RemoveRigidBody(IRigidbody* body) override;
	   
	    bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params, Actor* self) override;

		btDiscreteDynamicsWorld* GetWorld() { return mDynamicsWorld; }
	};
}