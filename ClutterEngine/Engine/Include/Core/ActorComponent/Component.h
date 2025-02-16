#pragma once
#include <Core/CCommon.h>

namespace clt
{
    class Actor;
    /**
     * @brief Base class for all components attached to an Actor.
     */
    class CLUTTER_API Component
    {
    protected:
        bool mIsEnable = true; ///< Indicates if the component is active.
        int mUpdateOrder = 0; ///< The order in which the component is updated.
        Actor* mOwner; ///< The actor that owns this component.

    public:
        /**
         * @brief Constructor for Component.
         * @param pOwner The actor that owns this component.
         * @param pUpdateOrder The order in which the component is updated.
         */
        Component(Actor* pOwner, int pUpdateOrder = 0) : mUpdateOrder(pUpdateOrder), mOwner(pOwner) {};

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

        /**
         * @brief Enables or disables the component.
         * @param pEnable True to enable the component, false to disable it.
         */
        void Enable(bool pEnable) { mIsEnable = pEnable; };

        /**
         * @brief Called when the component is destroyed.
         */
        void OnDestroy() {};

        /**
         * @brief Checks if the component is enabled.
         * @return True if the component is enabled, false otherwise.
         */
        bool IsEnable() const { return mIsEnable; }

        /**
         * @brief Gets the update order of the component.
         * @return The update order of the component.
         */
        int GetUpdateOrder() const { return mUpdateOrder; }

        friend Actor;
    };
}
