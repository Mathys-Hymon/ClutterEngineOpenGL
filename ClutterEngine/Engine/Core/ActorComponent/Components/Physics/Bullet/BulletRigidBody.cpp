#include "pch.h"
#include <Core/ActorComponent/Components/Physics/Bullet/BulletRigidBody.h>
#include <Core/ActorComponent/Components/Physics/Bullet/BulletCollider.h>
#include <Physics/Bullet/BulletPhysics.h>
#include <Core/Levels/Level.h>
#include <Physics/IPhysics.h>

using namespace clt;

BulletRigidBody::BulletRigidBody() :
    mWorld(nullptr), mBody(nullptr), mMotionState(nullptr), mShapes(nullptr), mMass(0.0f)
{
    mShapes = new btCompoundShape();

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 0, 0));

    btVector3 inertia(0, 0, 0);
    if (mMass != 0.0f)  mShapes->calculateLocalInertia(mMass, inertia);

    mMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, mMotionState, mShapes, inertia);
    mBody = new btRigidBody(rbInfo);
}

BulletRigidBody::~BulletRigidBody()
{
    if (mBody)
    {
        if(mWorld) mWorld->GetWorld()->removeRigidBody(mBody);
        delete mBody;
    }
    delete mMotionState;
    delete mShapes;
}

void BulletRigidBody::SetWorld(BulletPhysics* world)
{
    mWorld = world;
}

void BulletRigidBody::Start()
{
    auto collider = mOwner->GetComponentOfType<BulletCollider>();
    if (collider) AttachCollider(collider);
    //mOwner->GetLevel()->GetPhysics().AddRigidbody(this);

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

    Vector3 localPos = bulletCol->GetRelativeLocation();
    btTransform localTransform;
    localTransform.setIdentity();
    localTransform.setOrigin(btVector3(localPos.x, localPos.y, localPos.z));

    mShapes->addChildShape(localTransform, bulletCol->GetShape());

    // Recalculer l'inertie si le body est dynamique
    if (mMass != 0.0f) 
    {
        btVector3 inertia(0, 0, 0);
        mShapes->calculateLocalInertia(mMass, inertia);
        mBody->setMassProps(mMass, inertia);
    }
}

void BulletRigidBody::RemoveCollider(ICollider* collider)
{
    auto bulletCol = dynamic_cast<BulletCollider*>(collider);

    mShapes->removeChildShape(bulletCol->GetShape());

    if (mMass != 0.0f)
    {
        btVector3 inertia(0, 0, 0);
        mShapes->calculateLocalInertia(mMass, inertia);
        mBody->setMassProps(mMass, inertia);
    }
}
