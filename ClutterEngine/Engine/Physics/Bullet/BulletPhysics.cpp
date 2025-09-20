#include "pch.h"
#include "BulletPhysics.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>
#include <Core/CEngine.h>

using namespace clt;

BulletPhysics::BulletPhysics(CEngine& engine) : mEngine(engine)
{

    mDebug = new BulletDebugDraw(engine);

    mBroadphase = new btDbvtBroadphase();
    mCollisionConfig = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfig);
    mSolver = new btSequentialImpulseConstraintSolver();
    mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfig);

    mDynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

    if (engine.IsEditorMode())
    {
        mDynamicsWorld->setDebugDrawer(mDebug);
        mDebug->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawContactPoints);
    }
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

    mDynamicsWorld->debugDrawWorld();
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

bool BulletPhysics::LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params, Actor* self)
{
    if (!mDynamicsWorld) return false;

    Vector3 end = start + direction.Normalized() * maxDistance;

    btVector3 btStart(start.x, start.y, start.z);
    btVector3 btEnd(end.x, end.y, end.z);

    btCollisionWorld::ClosestRayResultCallback rayCallback(btStart, btEnd);

    rayCallback.m_collisionFilterGroup = static_cast<int>(params.Channel);
    rayCallback.m_collisionFilterMask = params.CollisionMask;

    mDynamicsWorld->rayTest(btStart, btEnd, rayCallback);

    if (rayCallback.hasHit())
    {
        const btCollisionObject* obj = rayCallback.m_collisionObject;
        if (obj)
        {
            auto* actorPtr = static_cast<Actor*>(obj->getUserPointer());

            if (params.IgnoreActor && actorPtr == self) return false;

            outHit.HitResult = true;
            outHit.Actor = actorPtr;

            if (actorPtr) outHit.Collider = actorPtr->GetComponentOfType<ColliderComponent>();

            btVector3 point = rayCallback.m_hitPointWorld;
            btVector3 normal = rayCallback.m_hitNormalWorld;

            outHit.Point = Vector3(point.x(), point.y(), point.z());
            outHit.Normal = Vector3(normal.x(), normal.y(), normal.z());
            outHit.Distance = (outHit.Point - start).Length();

            return true;
        }
    }

    outHit.HitResult = false;
    return false;
}
