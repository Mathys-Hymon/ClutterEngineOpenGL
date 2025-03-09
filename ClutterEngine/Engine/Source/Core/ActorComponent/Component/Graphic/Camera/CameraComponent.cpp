#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;

CameraComponent* CameraComponent::ACTIVE_CAMERA = nullptr;


CameraComponent::CameraComponent(float pFOV, ProjectionMode pMode, float pNearPlane, float pFarPlane) : Component(), mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane) { mDirty = true; }

void CameraComponent::UpdateMatrices()
{
	if (mProjectionMode == ProjectionMode::Perspective)
	{
		mProj = Matrix4Row::CreatePerspectiveFOV(mFov, mViewSize.x, mViewSize.y, mNearPlane, mFarPlane);
	}
	else
	{
		mProj = Matrix4Row::CreateOrtho(mViewSize.x, mViewSize.y, -1, mFarPlane);
	}
	mDirty = false;
}

void CameraComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);

	if (!ACTIVE_CAMERA)
	{
		ACTIVE_CAMERA = this;
	}

	mViewSize = mOwner->GetLevel()->GetRenderer().GetEngine()->GetWindow()->GetDimensions();
	mDirty = true;
}


void CameraComponent::Update()
{
	if (ACTIVE_CAMERA == this) mView = Matrix4Row::CreateLookAt(GetWorldLocation(), GetWorldLocation() + GetWorldTransform().Forward() * 100, GetWorldTransform().Up());
}

void CameraComponent::SetFOV(float pFOV)
{
	mFov = pFOV;
	mDirty = true;
}

void CameraComponent::SetProjectionMode(ProjectionMode pProjectionMode)
{
	mProjectionMode = pProjectionMode;
	mDirty = true;
}

void CameraComponent::SetActive(CameraComponent* cam)
{
	ACTIVE_CAMERA = cam;
}

CameraComponent* CameraComponent::GetActiveCamera()
{
	return ACTIVE_CAMERA;
}