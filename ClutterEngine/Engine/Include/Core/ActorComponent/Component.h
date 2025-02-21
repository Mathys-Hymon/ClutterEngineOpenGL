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

        Vector2 mRelativePosition = Vector2::ZERO;
        Vector2 mRelativeScale = Vector2::ONE;
        float mRelativeRotation = 0.0f;

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

        void SetRelativePosition(const Vector2& loc) { mRelativePosition = loc; };
        void SetRelativeScale(const Vector2& scale)  { mRelativeScale = scale;  };
        void SetRelativeRotation(float rot)          { mRelativeRotation = rot; };

        Vector2 GetRelativePosition() const { return mRelativePosition; };
        Vector2 GetRelativeScale()    const { return mRelativeScale;    };
        float GetRelativeRotation()   const { return mRelativeRotation; };

        Vector2 GetWorldPosition() const  { return mOwner->GetPosition() + mRelativePosition; };
        Vector2 GetWorldScale()    const  { return mOwner->GetScale() * mRelativeScale;       };
        float GetWorldRotation()   const  { return mOwner->GetRotation() + mRelativeRotation; };

        friend Actor;
    };
}
