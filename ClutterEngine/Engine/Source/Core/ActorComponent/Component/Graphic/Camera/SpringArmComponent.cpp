#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/SpringArmComponent.h>
#include <Core/Timer.h>

using namespace clt;

SpringArmComponent::SpringArmComponent(Actor* pCamera,float pLagSpeed, int pUpdateOrder) : Component(pUpdateOrder), mCamera(pCamera), mLagSpeed(pLagSpeed), mLagMaxDistance(0), mRotationLagSpeed(0), mArmLength(0), mCameraOffset(0)
{
}

void SpringArmComponent::Update()
{
    if (mCamera)
    {
        Vector2 targetLoc;

        if (mLagSpeed == 0)
        {
            targetLoc = GetWorldPosition() + mCameraOffset;
            mCamera->SetActorLocation(targetLoc);
        }
        else
        {
            targetLoc = Vector2::VInterp(mCamera->GetPosition(), GetWorldPosition() + mCameraOffset, Timer::deltaTime, mLagSpeed);
            mCamera->SetActorLocation(targetLoc);
        }
    }
}
