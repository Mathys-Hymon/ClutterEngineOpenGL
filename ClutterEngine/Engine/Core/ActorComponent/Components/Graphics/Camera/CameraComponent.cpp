#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;

CameraComponent* CameraComponent::ACTIVE_CAMERA = nullptr;


CameraComponent::CameraComponent(float pFOV, ProjectionMode pMode, float pNearPlane, float pFarPlane) : Component(), mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane), mOrthoHeight(10) { mDirty = true; }

CameraComponent::~CameraComponent()
{
	if (ACTIVE_CAMERA == this)
	{
		ACTIVE_CAMERA = nullptr;
	}
}

void CameraComponent::UpdateMatrices()
{
	if (mProjectionMode == ProjectionMode::Perspective)
	{
		mProj = Matrix4Row::CreatePerspectiveFOV(mFov, mViewSize.x, mViewSize.y, mNearPlane, mFarPlane);
	}
	else
	{
		float orthoWidth = mOrthoHeight * (mViewSize.x / mViewSize.y);

		mProj = Matrix4Row::CreateOrtho(orthoWidth, mOrthoHeight, -mFarPlane, mFarPlane);
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

	mViewSize = Window::Get().GetDimensions();
	mDirty = true;
}


void CameraComponent::Update()
{
	if (ACTIVE_CAMERA == this) mView = Matrix4Row::CreateLookAt(GetWorldLocation(), GetWorldLocation() - GetWorldTransform().Forward() * 100, GetWorldTransform().Up());
}

void CameraComponent::SetFOV(float pFOV)
{
	mFov = pFOV;
	mDirty = true;
}

void CameraComponent::SetOrthoHeight(float pHeight)
{
	mOrthoHeight = pHeight;
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

void CameraComponent::SetActive()
{
	ACTIVE_CAMERA = this;
}

CameraComponent* CameraComponent::GetActiveCamera()
{
	return ACTIVE_CAMERA;
}