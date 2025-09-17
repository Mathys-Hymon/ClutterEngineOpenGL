#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>

using namespace clt;

BulletCollider::BulletCollider() : mShape(nullptr), mType(ColliderShapeType::Box), mIsTrigger(false)
{
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

void BulletCollider::SetShape(ColliderShapeType type, const Vector3& size)
{
    if (mShape) delete mShape;
    mType = type;
    switch (type)
    {
    case ColliderShapeType::Box:mShape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
        break;
    case ColliderShapeType::Sphere: mShape = new btSphereShape(size.x * 0.5f);
        break;
    case ColliderShapeType::Capsule:
        break;
    case ColliderShapeType::Mesh:
        break;
    case ColliderShapeType::Plane:
        break;
    default:  mShape = new btBoxShape(btVector3(1, 1, 1));
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
