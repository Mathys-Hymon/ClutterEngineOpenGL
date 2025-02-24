#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;

CameraComponent* CameraComponent::ACTIVE_CAMERA = nullptr;


CameraComponent::CameraComponent(float pFOV, ProjectionMode pMode, float pNearPlane, float pFarPlane) : mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane), mZoom(1.0f) {}

void CameraComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);

	if (!ACTIVE_CAMERA)
	{
		ACTIVE_CAMERA = this;
	}

	mViewSize = mOwner->GetLevel()->GetRenderer().GetEngine().GetWindow()->GetDimensions();
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}


void CameraComponent::Update()
{
	if (ACTIVE_CAMERA == this)
	{
		UpdateViewMatrix();
	}
}

void CameraComponent::SetFOV(float pFOV)
{
	mFov = pFOV;
	UpdateProjectionMatrix();
}

void CameraComponent::SetProjectionMode(ProjectionMode pProjectionMode)
{
	mProjectionMode = pProjectionMode;
	UpdateProjectionMatrix();
}

void CameraComponent::SetActive(CameraComponent* cam)
{
	ACTIVE_CAMERA = cam;
}

CameraComponent* CameraComponent::GetActiveCamera()
{
	return ACTIVE_CAMERA;
}

void CameraComponent::UpdateViewMatrix()
{
	Vector2 tempPos = mOwner->GetPosition() + mRelativeTransform.location;
	glm::vec2 pos = tempPos.ToGlm();

	mView = glm::mat4(1.0f);
	mView = glm::translate(mView, glm::vec3(pos.x, pos.y, 0.0f));
	mView = glm::rotate(mView, glm::radians(-mRelativeTransform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	mView = glm::scale(mView, glm::vec3(-mZoom, -mZoom, 1.0f));
}

void CameraComponent::UpdateProjectionMatrix()
{
	if (mProjectionMode == ProjectionMode::Orthographic)
	{
		mProjection = glm::ortho(
			-mViewSize.x / 2,    // Left
			 mViewSize.x / 2,    // Right
			 mViewSize.y / 2,    // Bottom
			-mViewSize.y / 2,    // Top
			-1.0f,				 // Near
			 mFarPlane			 // Far
		);
	}
	else    // PERSPECTIVE PROJECTION
	{
		float aspectRatio = mViewSize.x / mViewSize.y;

		mProjection = glm::perspective(
			glm::radians(mFov),			// FOV
			aspectRatio,			   // Aspect Ratio
			mNearPlane,
			mFarPlane
		);
	}
}

