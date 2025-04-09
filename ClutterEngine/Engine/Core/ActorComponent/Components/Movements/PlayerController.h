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
        bool mIsSprinting;
        bool mIsCrouched;

        float mJumpHeight;
        int mJumpAmount;

        float mMaxWalkSpeed; ///< Speed of the player.  
        float mMaxSprintSpeed;

        float mMaxAcceleration;

        float mAirControl;

        Vector2 mMouseSpeed;

        virtual void OnCollisionEnter(const clt::hitResult& result) override {};
        virtual void OnCollisionStay(const clt::hitResult& result)  override {};
        virtual void OnCollisionExit(const clt::hitResult& result)  override {};

        virtual void OnTriggerEnter(const clt::hitResult& result) override {};
        virtual void OnTriggerStay(const clt::hitResult& result)  override {};
        virtual void OnTriggerExit(const clt::hitResult& result)  override {};
	};
}