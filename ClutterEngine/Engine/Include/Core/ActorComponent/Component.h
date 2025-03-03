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

        Transform mRelativeTransform;

        virtual void SetOwner(Actor* pOwner) 
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
        void Start() {};

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

        void SetRelativePosition(const Vector3& loc)      { mRelativeTransform.Location() = loc; };
        void SetRelativeScale(const Vector3& scale)       { mRelativeTransform.Scale() = scale; };
        void SetRelativeRotation(Quaternion rot)               { mRelativeTransform.Rotation() = rot; };
        void SetRelativeTransform(Transform& transform) { mRelativeTransform = transform;    };

        Vector3 GetRelativePosition()      const { return mRelativeTransform.Location(); };
        Vector3 GetRelativeScale()         const { return mRelativeTransform.Scale();    };
        Quaternion GetRelativeRotation()        const { return mRelativeTransform.Rotation(); };
        Transform GetRelativeTransform() const { return mRelativeTransform;          };

        Vector3 GetWorldPosition()         const { return mOwner->GetActorLocation() + mRelativeTransform.Location(); };
        Vector3 GetWorldScale()            const { return mOwner->GetScale() * mRelativeTransform.Scale();       };
        float GetWorldRotation()           const { return mOwner->GetRotation() + mRelativeTransform.Rotation(); };
        Transform GetWorldTransform()    const { return mOwner->getTransform() + mRelativeTransform;         };

        Actor* GetOwner() const { return mOwner; };

        friend Actor;
    };
}
