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
	    CLUTTER_CLASS(PlayerController);
		
	    void SetupProperties() override 
	    {
	        CPROPERTY(mJumpHeight, clt::PropMode::ReadWrite);
	    	CPROPERTY(mJumpAmount, clt::PropMode::ReadWrite);
	    	CPROPERTY(mAirControl, clt::PropMode::ReadWrite);
	    	
	    	CPROPERTY(mMaxWalkSpeed, clt::PropMode::ReadWrite);
	    	CPROPERTY(mMaxSprintSpeed, clt::PropMode::ReadWrite);
	    	CPROPERTY(mMaxAcceleration, clt::PropMode::ReadWrite);
	    	
	    	CPROPERTY(mMouseSpeed, clt::PropMode::ReadWrite);
	    }
		
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

        virtual void OnCollisionEnter(ColliderComponent* collider, const HitResult& result) override {};
        virtual void OnCollisionStay(ColliderComponent* collider, const HitResult& result)  override {};
        virtual void OnCollisionExit(ColliderComponent* collider, const HitResult& result)  override {};

        virtual void OnTriggerEnter(ColliderComponent* collider, const HitResult& result) override {};
        virtual void OnTriggerStay(ColliderComponent* collider, const HitResult& result)  override {};
        virtual void OnTriggerExit(ColliderComponent* collider, const HitResult& result)  override {};
	};
}