#include "pch.h"
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>
#include <Core/CEngine.h>
#include <Core/Levels/Level.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace clt;


void CameraComponent::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);

	mViewSize = mOwner->GetLevel()->GetRenderer().GetEngine().GetWindow()->GetDimensions();

	UpdateProjectionMatrix();
	UpdateViewMatrix();
}

CameraComponent::CameraComponent(ProjectionMode pMode, float pFOV, float pNearPlane, float pFarPlane) : mProjectionMode(pMode), mFov(pFOV), mNearPlane(pNearPlane), mFarPlane(pFarPlane) {}

void CameraComponent::Update()
{
	UpdateViewMatrix();
}

void CameraComponent::UpdateViewMatrix()
{
}

void CameraComponent::UpdateProjectionMatrix()
{
	if (mProjectionMode == ProjectionMode::Orthographic)
	{
		mProjection = glm::ortho(
			-mViewSize.x / 2.0f,
			 mViewSize.x / 2.0f,
			-mViewSize.y / 2.0f,
			 mViewSize.y / 2.0f,
			-1.0f, 1.0f
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