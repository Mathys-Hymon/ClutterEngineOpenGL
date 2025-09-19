#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>

using namespace clt;

BulletCollider::BulletCollider(ColliderShapeType shape, Vector3 bounds) : ICollider(0), mShape(nullptr), mType(shape), mIsTrigger(false)
{
    SetShape(shape, bounds);
}

BulletCollider::~BulletCollider()
{
    if (mShape) delete mShape;
}

void BulletCollider::Start()
{
    auto rb = mOwner->GetComponentOfType<BulletRigidBody>();

    if (rb) rb->AttachCollider(this);
}

void BulletCollider::SetShape(ColliderShapeType shape, Vector3 bounds)
{
    if (mShape) delete mShape;
    mType = shape;

    Vector3 bulletBounds = bounds * 2;

    switch (mType)
    {
    case ColliderShapeType::Box:
        mShape = new btBoxShape(btVector3(
            bulletBounds.x * 0.5f,
            bulletBounds.y * 0.5f,
            bulletBounds.z * 0.5f));
        break;

    case ColliderShapeType::Sphere:
        mShape = new btSphereShape(bulletBounds.x * 0.5f);
        break;

    case ColliderShapeType::Capsule:
        // x = radius, y = height
        mShape = new btCapsuleShape(bulletBounds.x, bulletBounds.y - 2 * bulletBounds.x);
        break;

    case ColliderShapeType::Mesh:

        mShape = nullptr; // temporary
        break;

    case ColliderShapeType::Plane:
        mShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
        break;

    default:
        mShape = new btBoxShape(btVector3(2.5f, 2.5f, 2.5f));
        break;
    }
}

ColliderShapeType BulletCollider::GetShapeType() const
{
    return mType;
}

void BulletCollider::SetIsTrigger(bool trigger)
{
    mIsTrigger = trigger;
}

bool BulletCollider::IsTrigger() const
{
    return false;
}

void BulletCollider::SetFriction(float friction)
{
}

float BulletCollider::GetFriction() const
{
    return 0.0f;
}

void BulletCollider::SetBounciness(float bounciness)
{
}

float BulletCollider::GetBounciness() const
{
    return 0.0f;
}

void BulletCollider::Subscribe(ICollisionListener* listener)
{
}
