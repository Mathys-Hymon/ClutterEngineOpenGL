#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/Timer.h>

using namespace clt;

SpringArmComponent::SpringArmComponent(Actor* pCamera,float pLagSpeed, int pUpdateOrder) : Component(pUpdateOrder), mCameraActor(pCamera), mLagSpeed(pLagSpeed), mLagMaxDistance(0), mRotationLagSpeed(0), mArmLength(0), mCameraOffset(0), mCameraComponent(nullptr)
{
}

SpringArmComponent::SpringArmComponent(CameraComponent* camera, float pLagSpeed, int pUpdateOrder) : Component(pUpdateOrder), mCameraActor(nullptr), mLagSpeed(pLagSpeed), mLagMaxDistance(0), mRotationLagSpeed(0), mArmLength(0), mCameraOffset(0), mCameraComponent(camera)
{
}

clt::SpringArmComponent::SpringArmComponent(float pLagSpeed, int pUpdateOrder) : Component(pUpdateOrder), mCameraActor(nullptr), mLagSpeed(pLagSpeed), mLagMaxDistance(0), mRotationLagSpeed(0), mArmLength(0), mCameraOffset(0), mCameraComponent(nullptr)
{
}

void SpringArmComponent::Start()
{
    if (!mCameraActor && !mCameraComponent)
    {
        mCameraComponent = mOwner->GetComponentOfType<clt::CameraComponent>();
    }
}

void SpringArmComponent::Update()
{
    if (mCameraActor)
    {
        Vector3 targetLoc;

        if (mLagSpeed == 0)
        {
            targetLoc = GetWorldLocation() + mCameraOffset;
            mCameraActor->SetActorLocation(targetLoc);
        }
        else
        {
            targetLoc = Vector3::VInterp(mCameraActor->GetActorLocation(), GetWorldLocation() + mCameraOffset, mLagSpeed);
            mCameraActor->SetActorLocation(targetLoc);
        }
    }
    else if (mCameraComponent)
    {
        Vector3 targetLoc;

        if (mLagSpeed == 0)
        {
            targetLoc = GetWorldLocation() + mCameraOffset;
            mCameraComponent->SetWorldLocation(targetLoc);
        }
        else
        {
            targetLoc = Vector3::VInterp(mCameraComponent->GetWorldLocation(), GetWorldLocation() + mCameraOffset, mLagSpeed);
            mCameraComponent->SetWorldLocation(targetLoc);
        }
    }
}
