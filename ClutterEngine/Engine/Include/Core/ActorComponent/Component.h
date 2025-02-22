#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Actor.h>

namespace clt
{
    /**
     * @brief Base class for all components attached to an Actor.
     */
    class CLUTTER_API Component
    {

    protected:
        bool mIsActive = true; ///< Indicates if the component is active.
        int mUpdateOrder = 0; ///< The order in which the component is updated.
        Actor* mOwner; ///< The actor that owns this component.

        Transform2D mRelativeTransform;

        void SetOwner(Actor* pOwner) 
        { 
            mOwner = pOwner; 
            Start();
        };

    public:
        /**
         * @brief Constructor for Component.
         * @param pOwner The actor that owns this component.
         * @param pUpdateOrder The order in which the component is updated.
         */
        Component(int pUpdateOrder = 0) : mUpdateOrder(pUpdateOrder), mOwner(nullptr) {};

        /**
         * @brief Virtual destructor for Component.
         */
        virtual ~Component() = default;

        /**
         * @brief Called when the component is started.
         */
        virtual void Start() {};

        /**
         * @brief Called every frame to update the component.
         */
        virtual void Update() {};

        virtual void Unload() {};

        /**
         * @brief Enables or disables the component.
         * @param pEnable True to enable the component, false to disable it.
         */
        void SetActive(bool pActive) { mIsActive = pActive; };

        /**
         * @brief Called when the component is destroyed.
         */
        void OnDestroy() {};

        /**
         * @brief Checks if the component is enabled.
         * @return True if the component is enabled, false otherwise.
         */
        bool IsActive() const { return mIsActive; }

        /**
         * @brief Gets the update order of the component.
         * @return The update order of the component.
         */
        int GetUpdateOrder() const { return mUpdateOrder; }

        void SetRelativePosition(const Vector2& loc)      { mRelativeTransform.location = loc; };
        void SetRelativeScale(const Vector2& scale)       { mRelativeTransform.scale = scale;  };
        void SetRelativeRotation(float rot)               { mRelativeTransform.rotation = rot; };
        void SetRelativeTransform(Transform2D& transform) { mRelativeTransform = transform;    };

        Vector2 GetRelativePosition()      const { return mRelativeTransform.location; };
        Vector2 GetRelativeScale()         const { return mRelativeTransform.scale;    };
        float GetRelativeRotation()        const { return mRelativeTransform.rotation; };
        Transform2D GetRelativeTransform() const { return mRelativeTransform;          };

        Vector2 GetWorldPosition() const  { return mOwner->GetPosition() + mRelativeTransform.location; };
        Vector2 GetWorldScale()    const  { return mOwner->GetScale() * mRelativeTransform.scale;       };
        float GetWorldRotation()   const  { return mOwner->GetRotation() + mRelativeTransform.rotation; };

        friend Actor;
    };
}
