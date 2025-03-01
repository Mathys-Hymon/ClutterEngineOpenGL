#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform2D.h>
#include <unordered_map>
#include <vector>

/**
 * @brief Enum representing the state of an actor.
 */
enum class CLUTTER_API ActorState {
    Active, ///< The actor is active.
    Paused, ///< The actor is paused.
    Dead    ///< The actor is dead.
};

namespace clt
{
    class Component;
    class Level;
    class CLUTTER_API Actor
    {
        /**
         * @brief Internal method to update the actor.
         */
        void InternalUpdate();

        /**
         * @brief Internal method to add a component to the actor.
         * @param pComponent The component to add.
         */
        void AddComponentInternal(Component* pComponent);

        bool mIsUpdatingComponents; ///< Flag indicating if components are being updated.

    protected:
        std::string mName;
        ActorState mState; ///< The state of the actor.
        Level* mLevel; ///< The scene the actor is attached to.
        Transform2D mTransform; ///< The transform of the actor.

        std::unordered_map<size_t, Component*> mComponents; ///< Map of components by their ID.
        std::vector<Component*> mComponentsByUpdateOrder; ///< Components ordered by update order.
        std::vector<Component*> mComponentsToAdd; ///< Components to be added.
        std::vector<Component*> mComponentsToRemove; ///< Components to be removed.

    public:
        /**
         * @brief Constructor for the Actor class.
         */
        Actor(std::string pName);

        /**
         * @brief Destructor for the Actor class.
         */
        ~Actor();

        /**
         * @brief Virtual method to update the actor.
         */
        virtual void Update() {};

        /**
         * @brief Adds a component to the actor.
         * @param pComponent The component to add.
         */
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args);

        /**
         * @brief Removes a component of type T from the actor.
         */
        template<typename T>
        void RemoveComponent();

        template<typename T>
        T* GetComponentOfType()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

            size_t hashCode = typeid(T).hash_code();
            auto it = mComponents.find(hashCode);
            if (it != mComponents.end()) {
                return static_cast<T*>(it->second);
            }
            else
            {
                return nullptr;
            }
        };

        /**
         * @brief Attaches the actor to a scene.
         * @param pScene The scene to attach to.
         */
        void AttachLevel(Level* pScene);

        /**
         * @brief Gets the transform of the actor.
         * @return The transform of the actor.
         */
        Transform2D getTransform() const { return mTransform; };

        /**
         * @brief Gets the position of the actor.
         * @return The position of the actor.
         */
        Vector2 GetActorLocation() const { return mTransform.location; };

        /**
         * @brief Gets the scale of the actor.
         * @return The scale of the actor.
         */
        Vector2 GetScale() const { return mTransform.scale; };

        std::string GetName() const { return mName; };

        float GetRotation() const { return mTransform.rotation; };
        /**
         * @brief Virtual method called when the actor collides with another actor.
         * @param other The other actor.
         */
        virtual void OnCollision(Actor* other) {};

        /**
         * @brief Virtual method called when the collision with another actor ends.
         * @param other The other actor.
         */
        virtual void OnCollisionEnd(Actor* other) {};

        /**
         * @brief Sets the location of the actor.
         * @param loc The new location.
         */
        void SetActorLocation(Vector2 loc) { mTransform.location = loc; };

        /**
         * @brief Sets the scale of the actor.
         * @param scale The new scale.
         */
        void SetActorScale(Vector2 scale) { mTransform.scale = scale; };
        void SetActorScale(float scale) { mTransform.scale = {scale, scale}; };
        /**
         * @brief Sets the rotation of the actor.
         * @param rot The new rotation.
         */
        void SetActorRotation(float rot) { mTransform.rotation = rot; };

        /**
         * @brief Adds an offset to the actor's location.
         * @param locOffset The location offset.
         */
        void AddActorLocationOffset(Vector2 locOffset) { mTransform.location += locOffset; };

        /**
         * @brief Adds an offset to the actor's rotation.
         * @param rotOffset The rotation offset.
         */
        void AddActorRotationOffset(float rotOffset) { mTransform.rotation += rotOffset; };

        /**
         * @brief Gets the level the actor is attached to.
         * @return The level the actor is attached to.
         */
        Level* GetLevel() const { return mLevel; };

        friend Level;
    };

    template<typename T, typename... Args>
    inline T* Actor::AddComponent(Args&&... args) {
        size_t hashCode = typeid(T).hash_code();

        if (mComponents.find(hashCode) != mComponents.end()) {
            std::cerr << "A component of this type already exists in the Actor.\n";
            return nullptr;
        }
        else {
            T* pComponent = new T(std::forward<Args>(args)...);
            if (mIsUpdatingComponents) mComponentsToAdd.emplace_back(pComponent);
            else AddComponentInternal(pComponent);

            return pComponent;
        }
    }
}
