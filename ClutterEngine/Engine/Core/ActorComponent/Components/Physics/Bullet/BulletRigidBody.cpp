#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>

using namespace clt;

BulletRigidBody::BulletRigidBody(BulletPhysics* world) :
    mWorld(world), mBody(nullptr), mMotionState(nullptr), mShape(nullptr), mMass(0.0f)
{}

BulletRigidBody::~BulletRigidBody()
{
    if (mBody)
    {
        mWorld->GetWorld()->removeRigidBody(mBody);
        delete mBody;
    }
    delete mMotionState;
    delete mShape;
}

void BulletRigidBody::Start()
{
    auto collider = mOwner->GetComponentOfType<BulletCollider>();
    if (collider) AttachCollider(collider);

    Vector3 worldPos = GetWorldLocation();
    Quaternion worldRot = GetWorldRotation();

    btTransform transform;
    transform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));
    transform.setRotation(btQuaternion(worldRot.x, worldRot.y, worldRot.z, worldRot.w));

    mBody->setWorldTransform(transform);
    mBody->getMotionState()->setWorldTransform(transform);
}

void BulletRigidBody::SyncFromBullet()
{
    btTransform transform = mBody->getWorldTransform();
    btVector3 pos = transform.getOrigin();
    btQuaternion rot = transform.getRotation();

    SetWorldLocation(Vector3(pos.x(), pos.y(), pos.z()));
    SetWorldRotation(Quaternion(rot.w(), rot.x(), rot.y(), rot.z()));
}

void BulletRigidBody::SetMass(float mass)
{
    mMass = mass;
}

float BulletRigidBody::GetMass() const
{
    return mMass;
}

void BulletRigidBody::SetVelocity(const Vector3& vel)
{
    if (mBody) mBody->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
}

Vector3 BulletRigidBody::GetVelocity() const
{
    auto v = mBody->getLinearVelocity();
    return { v.getX(), v.getY(), v.getZ() };
}

void BulletRigidBody::SetCustomGravity(const Vector3& gravity)
{
    if (mBody) mBody->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

void BulletRigidBody::AddForce(const Vector3& force)
{
    if (mBody) mBody->applyCentralForce(btVector3(force.x, force.y, force.z));
}

void BulletRigidBody::AddImpulse(const Vector3& impulse)
{
    if (mBody) mBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
}

void BulletRigidBody::AddForceAtLocation(const Vector3& force, const Vector3& relativeLoc)
{
    if (mBody) mBody->applyForce(btVector3(force.x, force.y, force.z), btVector3(relativeLoc.x, relativeLoc.y, relativeLoc.z));
}

void BulletRigidBody::AddImpulseAtLocation(const Vector3& impulse, const Vector3& relativeLoc)
{
    if (mBody) mBody->applyImpulse(btVector3(impulse.x, impulse.y, impulse.z), btVector3(relativeLoc.x, relativeLoc.y, relativeLoc.z));
}

void BulletRigidBody::AttachCollider(ICollider* collider)
{
    auto bulletCol = dynamic_cast<BulletCollider*>(collider);
    mShape = bulletCol->GetShape();

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 0, 0));

    btVector3 inertia(0, 0, 0);
    if (mMass != 0.0f) mShape->calculateLocalInertia(mMass, inertia);

    mMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo info(mMass, mMotionState, mShape, inertia);
    mBody = new btRigidBody(info);

    mWorld->GetWorld()->addRigidBody(mBody);
}
