#pragma once  
#include <Core/ActorComponent/Component.h>  
#include <Core/ActorComponent/Components/Movements/PlayerController.h>  
#include <Physics/Collision/ICollisionListener.h>  
#include <Core/ActorComponent/Components/Physics/RigidBody.h>  

namespace clt  
{  
   class FlipbookComponent;  
   /**  
    * @brief PlayerController class responsible for handling player movements and collisions.  
    */  
   class CLUTTER_API PlayerController2D : public PlayerController
   {  
       FlipbookComponent* mSprite; ///< Pointer to the player's sprite component.  
       RigidBody* mRb; ///< Pointer to the player's rigid body component.  

   public:  
       /**  
        * @brief Constructor for PlayerController.  
        * @param pMovementCallback Callback function for movement.  
        * @param pJumpCallback Callback function for jump.  
        * @param pSpeed Speed of the player.  
        */  
       PlayerController2D(std::string pMovementCallback, std::string pJumpCallback = "", float pSpeed = 2);  
       ~PlayerController2D() = default;  

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

       virtual void SetOwner(Actor* pOwner) override;


       /**
* @brief Called when a collision starts.
* @param result The result of the collision.
*/
       virtual void OnCollisionEnter(ColliderComponent* collider, const HitResult& result) override;

       /**
        * @brief Called when a collision stays.
        * @param result The result of the collision.
        */
       virtual void OnCollisionStay(ColliderComponent* collider, const HitResult& result) override;

       /**
        * @brief Called when a collision ends.
        * @param result The result of the collision.
        */
       virtual void OnCollisionExit(ColliderComponent* collider, const HitResult& result) override;
   };  
}