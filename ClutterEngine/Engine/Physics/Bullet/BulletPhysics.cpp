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

    mDynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
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
    for (auto rb : mRigidbodies) rb->SyncToBullet();

    mDynamicsWorld->stepSimulation(Timer::deltaTime);

    for (auto rb : mRigidbodies)  rb->SyncFromBullet();
}

void BulletPhysics::AddRigidbody(IRigidbody* body)
{
    auto bulletRb = static_cast<BulletRigidBody*>(body);

    if (bulletRb && bulletRb->GetInternalBody())
    {
        bulletRb->SetWorld(this);
        mRigidbodies.push_back(bulletRb);
    };
}

void BulletPhysics::RemoveRigidBody(IRigidbody* body)
{
    auto bulletRb = static_cast<BulletRigidBody*>(body);

    mDynamicsWorld->addRigidBody(bulletRb->GetInternalBody());

    auto it = std::find(mRigidbodies.begin(), mRigidbodies.end(), bulletRb);
    if (it != mRigidbodies.end())  mRigidbodies.erase(it);

    delete bulletRb;
}

bool BulletPhysics::LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, raycastHit& hit, bool debugPersistant, Actor* self)
{
    return false;
}
