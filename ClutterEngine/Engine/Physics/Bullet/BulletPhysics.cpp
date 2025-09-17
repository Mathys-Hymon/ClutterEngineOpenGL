#include "pch.h"
#include "BulletPhysics.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>

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

    for (auto rb : mRigidbodies)
    {
        rb->SyncFromBullet();
    }
}

IRigidbody* BulletPhysics::CreateRigidbody()
{
    auto rigidbody = new BulletRigidBody(this);
    mRigidbodies.push_back(rigidbody);

    return rigidbody;
}

void BulletPhysics::DestroyRigidBody(IRigidbody* body)
{
    auto it = std::find(mRigidbodies.begin(), mRigidbodies.end(), body);
    if (it != mRigidbodies.end())  mRigidbodies.erase(it);

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
