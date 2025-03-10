#include "pch.h"
#include <Core/ActorComponent/Components/Movements/PlayerController.h>

using namespace clt;

PlayerController::PlayerController(float pSpeed) : mMaxWalkSpeed(pSpeed), mAirControl(0.1f), mIsJumping(false), mJumpHeight(230), mJumpAmount(1), mMaxSprintSpeed(pSpeed * 1.5f), mMovement(MovementMode::Walk), mIsCrouched(false), mIsSprinting(false)
{}
