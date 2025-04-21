#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Component.h>  
#include <Physics/Collision/ICollisionListener.h>  

namespace clt
{
    enum class MovementMode
    {
        Walk,
        Sprint,
        Crouch,
        Jump,
        Falling,
        Swim,
        Flying,
        Custom
    };

	class CLUTTER_API PlayerController : public Component, public ICollisionListener
	{
    public:

        PlayerController(float pSpeed = 2);
        ~PlayerController() = default;

        MovementMode mMovement;

        bool mIsJumping;
        bool mIsMoving;
        bool mIsSprinting;
        bool mIsCrouched;

        float mJumpHeight;
        int mJumpAmount;

        float mMaxWalkSpeed;
        float mMaxSprintSpeed;

        float mMaxAcceleration;

        float mAirControl;

        Vector2 mMouseSpeed;

        virtual void OnCollisionEnter(const hitResult& result) override {};
        virtual void OnCollisionStay(const hitResult& result)  override {};
        virtual void OnCollisionExit(const hitResult& result)  override {};

        virtual void OnTriggerEnter(const hitResult& result) override {};
        virtual void OnTriggerStay(const hitResult& result)  override {};
        virtual void OnTriggerExit(const hitResult& result)  override {};
	};
}