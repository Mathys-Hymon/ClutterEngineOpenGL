#include "pch.h"
#include "BulletPhysics.h"
#include <Core/ActorComponent/Components/Physics/IRigidbody.h>
#include <Core/ActorComponent/Components/Physics/ICollider.h>

using namespace clt;

BulletPhysics::BulletPhysics()
{
    mBroadphase = new btDbvtBroadphase();
    mCollisionConfig = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfig);
    mSolver = new btSequentialImpulseConstraintSolver();
    mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfig);

    mDynamicsWorld->setGravity(btVector3(0, 9.81f, 0));
}

BulletPhysics::~BulletPhysics()
{
    delete mDynamicsWorld;
    delete mSolver;
    delete mDispatcher;
    delete mCollisionConfig;
    delete mBroadphase;
}

void BulletPhysics::UpdatePhysics()
{
    mDynamicsWorld->stepSimulation(Timer::deltaTime);
}

IRigidbody* BulletPhysics::CreateRigidbody()
{
    return new BulletRigidbody(this);
}

void BulletPhysics::DestroyRigidBody(IRigidbody* body)
{
    delete body;
}

ICollider* BulletPhysics::CreateCollider()
{
    return new BulletCollider();
}

void BulletPhysics::DestroyCollider(ICollider* collider)
{
    delete collider;
}

bool BulletPhysics::LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, raycastHit& hit, bool debugPersistant, Actor* self)
{
    return false;
}
