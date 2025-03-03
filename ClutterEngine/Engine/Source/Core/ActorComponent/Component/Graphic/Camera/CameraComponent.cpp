#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;

CameraComponent* CameraComponent::ACTIVE_CAMERA = nullptr;


CameraComponent::CameraComponent(ProjectionMode pMode, float pFOV, float pNearPlane, float pFarPlane) : mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane) {}

void CameraComponent::UpdateProjViewMatrix()
{
	mViewProj = Matrix4Row::CreateSimpleViewProj(mViewSize.x, mViewSize.y);
}

void CameraComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);

	if (!ACTIVE_CAMERA)
	{
		ACTIVE_CAMERA = this;
	}

	mViewSize = mOwner->GetLevel()->GetRenderer().GetEngine()->GetWindow()->GetDimensions();
	UpdateProjViewMatrix();
}


void CameraComponent::Update()
{
	if (ACTIVE_CAMERA == this)
	{
		UpdateProjViewMatrix();
	}
}

void CameraComponent::SetFOV(float pFOV)
{
	mFov = pFOV;
	UpdateProjViewMatrix();
}

void CameraComponent::SetProjectionMode(ProjectionMode pProjectionMode)
{
	mProjectionMode = pProjectionMode;
	UpdateProjViewMatrix();
}

void CameraComponent::SetActive(CameraComponent* cam)
{
	ACTIVE_CAMERA = cam;
}

CameraComponent* CameraComponent::GetActiveCamera()
{
	return ACTIVE_CAMERA;
}