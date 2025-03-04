#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;

CameraComponent* CameraComponent::ACTIVE_CAMERA = nullptr;


CameraComponent::CameraComponent(ProjectionMode pMode, float pFOV, float pNearPlane, float pFarPlane) : mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane) { UpdateMatrices(); }

void CameraComponent::UpdateMatrices()
{
	mView = Matrix4Row::CreateLookAt(Vector3(0, 0, 5), Vector3::unitX, Vector3::unitZ);

	if (mProjectionMode == ProjectionMode::Perspective)
	{
		mProj = Matrix4Row::CreatePerspectiveFOV(70.0f, mViewSize.x, mViewSize.y, 0.01f, 10000.0f);
	}
	else
	{
		mProj = Matrix4Row::CreateOrtho(mViewSize.x, mViewSize.y, -1, mFarPlane);
	}
}

void CameraComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);

	if (!ACTIVE_CAMERA)
	{
		ACTIVE_CAMERA = this;
	}

	mViewSize = mOwner->GetLevel()->GetRenderer().GetEngine()->GetWindow()->GetDimensions();
	UpdateMatrices();
}


void CameraComponent::Update()
{
	if (ACTIVE_CAMERA == this)
	{
		UpdateMatrices();
	}
}

void CameraComponent::SetFOV(float pFOV)
{
	mFov = pFOV;
	UpdateMatrices();
}

void CameraComponent::SetProjectionMode(ProjectionMode pProjectionMode)
{
	mProjectionMode = pProjectionMode;
	UpdateMatrices();
}

void CameraComponent::SetActive(CameraComponent* cam)
{
	ACTIVE_CAMERA = cam;
}

CameraComponent* CameraComponent::GetActiveCamera()
{
	return ACTIVE_CAMERA;
}