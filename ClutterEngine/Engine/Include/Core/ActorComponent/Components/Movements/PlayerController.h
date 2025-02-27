#pragma once  
#include <Core/ActorComponent/Component.h>  
#include <Physics/Collision/ICollisionListener.h>  
#include <Core/ActorComponent/Components/Physics/RigidBody2D.h>  

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

   class FlipbookComponent;  
   /**  
    * @brief PlayerController class responsible for handling player movements and collisions.  
    */  
   class CLUTTER_API PlayerController : public Component, public ICollisionListener  
   {  
       FlipbookComponent* mSprite; ///< Pointer to the player's sprite component.  
       RigidBody2D* mRb; ///< Pointer to the player's rigid body component.  

       MovementMode mMovement;

   public:  

       bool mIsJumping;
       bool mIsSprinting;
       bool mIsCrouched;

       float mJumpHeight;
       int mJumpAmount;

       float mMaxWalkSpeed; ///< Speed of the player.  
       float mMaxSprintSpeed;

       float mAirControl;

       /**  
        * @brief Constructor for PlayerController.  
        * @param pMovementCallback Callback function for movement.  
        * @param pJumpCallback Callback function for jump.  
        * @param pSpeed Speed of the player.  
        */  
       PlayerController(std::string pMovementCallback, std::string pJumpCallback = "", float pSpeed = 2);  
       ~PlayerController() = default;  

       /**  
        * @brief Called when a collision starts.  
        * @param result The result of the collision.  
        */  
       virtual void OnCollisionEnter(const hitResult& result) override;  

       /**  
        * @brief Called when a collision stays.  
        * @param result The result of the collision.  
        */  
       virtual void OnCollisionStay(const hitResult& result) override;  

       /**  
        * @brief Called when a collision ends.  
        * @param result The result of the collision.  
        */  
       virtual void OnCollisionExit(const hitResult& result) override;  

       /**  
        * @brief Sets the owner of the component.  
        * @param pOwner Pointer to the owner actor.  
        */  
       virtual void SetOwner(Actor* pOwner) override;  

       /**  
        * @brief Handles player movement in a given direction.  
        * @param pDirection The direction vector for movement.  
        */  
       virtual void Movement(Vector2 pDirection);  

       /**  
        * @brief Handles player movement in a given direction.  
        * @param pDirection The direction scalar for movement.  
        */  
       virtual void Movement(float pDirection);  

       virtual void Update() override;

       /**  
        * @brief Handles player jump action.  
        */  
       virtual void Jump();  
   };  
}