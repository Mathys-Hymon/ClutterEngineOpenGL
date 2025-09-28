#include "pch.h"
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Input/Inputs.h>

using namespace clt;

EditorController::EditorController(float pMouseSpeed) : PlayerController(2), mMinSpeed(0.1f), mMaxSpeed(10.0f), mActualSpeed(1.0f), mMainCam(false), mCanMove(true), mFirstClick(true), mRot(0,0)
{
	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });

	Inputs::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "CameraMovement");
	Inputs::Get().MapKeysToAxis(EKey::E, EKey::Q, "VerticalMovement");

	Inputs::Get().MapKeyToAction(EKey::Escape, "UnfocusGame");

	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
	Inputs::Get().RegisterVectCallback("CameraMovement", [this](Vector2 value) { this->Movement(value); });
	Inputs::Get().RegisterAxisCallback("VerticalMovement", [this](float value) { this->MoveVertically(value); });
	Inputs::Get().RegisterScrollCallback([this](float value) { this->ChangeSpeed(value); });
	Inputs::Get().RegisterActionCallback("UnfocusGame", [this] { this->UnfocusWindow(); });

	mMaxAcceleration = 1;
	mMaxWalkSpeed = 5;
	mMouseSpeed = pMouseSpeed;
}


void EditorController::Update()
{
	auto cam = mOwner->GetComponentOfType<CameraComponent>();

	if (!cam || !(cam == CameraComponent::GetActiveCamera())) mMainCam = false;
	else mMainCam = true;

	if (!mMainCam) return;

	Inputs& i = Inputs::Get();

	if (mCanMove)
	{
		if (i.IsButtonPressed(EMouseButton::Right))
		{
			Vector2 screenSize = Window::Get().GetDimensions();
			i.SetShowMouseCursor(false);

			if (mFirstClick) 
			{
				mFirstClick = false;
				i.SetMousePosition({ screenSize.x * 0.5f, screenSize.y * 0.5f });
				return;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(Window::Get().GetGLFWWindow(), &mouseX, &mouseY);
			Vector2 currentMousePos(static_cast<float>(mouseX), static_cast<float>(mouseY));
			Vector2 mouseDelta = currentMousePos - Vector2{ screenSize.x * 0.5f, screenSize.y * 0.5f };

			i.SetMousePosition({ screenSize.x * 0.5f, screenSize.y * 0.5f });

			Rotation(mouseDelta);
		}
		else
		{	
			mFirstClick = true;
			i.SetShowMouseCursor(true);
		}

		if (i.IsButtonPressed(EKey::A)) Movement({ 1,0 });
		if (i.IsButtonPressed(EKey::D)) Movement({ -1,0 });
		if (i.IsButtonPressed(EKey::W)) Movement({ 0,1 });
		if (i.IsButtonPressed(EKey::S)) Movement({ 0,-1 });

		if (i.IsButtonPressed(EKey::E)) MoveVertically(1);
		if (i.IsButtonPressed(EKey::Q)) MoveVertically(-1);
	}
	else
	{
		i.SetShowMouseCursor(true);
	}

}

void EditorController::Movement(Vector2 pDirection)
{
	if (!mMainCam || !mCanMove) return;

	float dt = Timer::deltaTime;

	Vector3 forward = pDirection.y * mOwner->GetTransform().Forward() * dt;
	Vector3 right = pDirection.x * mOwner->GetTransform().Right() * dt;

	mOwner->AddActorLocationOffset((- forward + right) * mActualSpeed);
}

void EditorController::MoveVertically(float pDirection)
{
	if (!mMainCam || !mCanMove) return;

	Vector3 up = pDirection * mOwner->GetTransform().Up() * Timer::deltaTime;
	
	mOwner->AddActorLocationOffset(up * mActualSpeed);
}

void EditorController::ChangeSpeed(float pDirection)
{
	if (!mMainCam || !mCanMove) return;

	if (Inputs::Get().IsButtonPressed(EMouseButton::Right))
	{
		mActualSpeed = Maths::Clamp(mActualSpeed + (pDirection * 0.2f), mMinSpeed, mMaxSpeed);
	}
	else
	{
		Movement({ 0.0f , pDirection * 10.0f });
	}
}

void EditorController::UnfocusWindow()
{
	clt::Inputs::Get().SetShowMouseCursor(true);
	clt::Inputs::Get().LockMouseCursor(false);
}

void EditorController::Rotation(Vector2 pRotation)
{
	if (!mMainCam || !mCanMove) return;

	if (Inputs::Get().IsButtonPressed(EMouseButton::Right))
	{
		clt::Inputs::Get().SetShowMouseCursor(false);
		clt::Inputs::Get().LockMouseCursor(true);

		mRot.x += pRotation.x * 0.001f;
		mRot.y -= pRotation.y * 0.001f;

		mRot.y = Maths::Clamp(mRot.y, -Maths::PI_OVER2, Maths::PI_OVER2);

		Quaternion qYaw(Vector3::Up, mRot.x);
		Quaternion qPitch(Vector3::Right, mRot.y);
		Quaternion finalRot = Quaternion::Concatenate(qPitch, qYaw);

		mOwner->SetActorRotation(finalRot);
	}
	else
	{
		clt::Inputs::Get().SetShowMouseCursor(true);
		clt::Inputs::Get().LockMouseCursor(false);
	}
}
