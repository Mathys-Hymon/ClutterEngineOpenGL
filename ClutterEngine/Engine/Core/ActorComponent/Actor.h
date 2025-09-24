#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform.h>
#include <Physics/HitResult.h>
#include <Core/Timer.h>
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
    /**
     * @brief Represents an entity in the game world that can have components and a transform.
     * 
     * The Actor class is the base class for all objects that can be placed or spawned in a level.
     * It manages its own transform, state, and a collection of components that define its behavior.
     */
    class CLUTTER_API Actor
    {
        /**
         * @brief Internal method to update the actor and its components.
         * 
         * This method is called by the engine to update the actor and all its components.
         */
        void InternalUpdate();

        /**
         * @brief Internal method to add a component to the actor.
         * @param pComponent The component to add.
         * 
         * This method handles the actual insertion of the component into the actor's component list.
         */
        void AddComponentInternal(Component* pComponent);

        bool mIsUpdatingComponents; ///< Flag indicating if components are being updated.

        std::string mName; ///< The name of the actor.
        ActorState mState; ///< The state of the actor.
        Level* mLevel; ///< The scene the actor is attached to.
        Transform mTransform; ///< The transform of the actor.
        std::unordered_map<size_t, Component*> mComponents; ///< Map of components by their type hash code.
        std::vector<Component*> mComponentsByUpdateOrder; ///< Components ordered by update order.
        std::vector<Component*> mComponentsToAdd; ///< Components to be added after update.
        std::vector<size_t> mComponentsToRemove; ///< Components to be removed after update.

    public:
        /**
         * @brief Constructor for the Actor class.
         * @param pLevel The level to which this actor belongs.
         * @param pName The name of the actor (default: "Actor").
         */
        Actor(Level* pLevel, std::string pName = "Actor");

        /**
         * @brief Destructor for the Actor class.
         */
        ~Actor();

        /**
         * @brief Called when the actor is first created or spawned.
         * 
         * Override this method to implement custom initialization logic.
         */
        virtual void Start() {};

        /**
         * @brief Virtual method to update the actor.
         * 
         * Override this method to implement custom per-frame update logic.
         */
        virtual void Update() {};

        /**
         * @brief Called when the actor is being destroyed.
         * 
         * Override this method to implement custom cleanup logic.
         */
        virtual void Destroy() {};

        /**
         * @brief Adds a component of type T to the actor.
         * @tparam T The type of the component to add (must derive from Component).
         * @tparam Args Constructor argument types for the component.
         * @param args Arguments to forward to the component's constructor.
         * @return Pointer to the newly added component, or nullptr if a component of this type already exists.
         */
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args);

        /**
         * @brief Removes a component of type T from the actor.
         * @tparam T The type of the component to remove (must derive from Component).
         * 
         * If the component exists, it will be removed after the current update cycle.
         */
        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

            size_t hashCode = typeid(T).hash_code();
            if (mComponents.find(hashCode) != mComponents.end())
            {
                mComponentsToRemove.push_back(hashCode);
            }
        }

        /**
         * @brief Gets a pointer to the component of type T attached to this actor.
         * @tparam T The type of the component to retrieve (must derive from Component).
         * @return Pointer to the component if found, nullptr otherwise.
         */
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
         * @brief Performs a line trace (raycast) from a start point in a direction.
         * @param start The starting point of the trace.
         * @param direction The direction of the trace.
         * @param maxDistance The maximum distance to trace.
         * @param hit The result of the trace if a hit occurs.
         * @param debugPersistant Whether to persist debug visualization.
         * @param ignoreSelf Whether to ignore this actor in the trace.
         * @return True if something was hit, false otherwise.
         */
        bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params = {
                TraceChannel::Visibility,
                static_cast<uint16_t>(TraceChannel::All),
                nullptr,
                true,
                false,
                false });

        /**
         * @brief Gets the transform of the actor.
         * @return The transform of the actor.
         */
        Transform GetTransform() const { return mTransform; };

        /**
         * @brief Gets the position of the actor.
         * @return The position of the actor.
         */
        Vector3 GetActorLocation() const { return mTransform.Location(); };

        /**
         * @brief Gets the scale of the actor.
         * @return The scale of the actor.
         */
        Vector3 GetScale() const { return mTransform.Scale(); };

        /**
         * @brief Gets the name of the actor.
         * @return The name of the actor.
         */
        std::string GetName() const { return mName; };

        /**
         * @brief Gets the rotation of the actor as a quaternion.
         * @return The rotation of the actor.
         */
        Quaternion GetRotation() const { return mTransform.Rotation(); };

        /**
         * @brief Sets the location of the actor.
         * @param loc The new location.
         */
        void SetActorLocation(const Vector3& loc)
        { 
            mTransform.SetLocation(loc);
        };

        /**
         * @brief Sets the location of the actor using a 2D vector.
         * @param loc The new location.
         */
        void SetActorLocation(const Vector2& loc)
        {
            mTransform.SetLocation(loc);
        };

        /**
         * @brief Sets the scale of the actor.
         * @param scale The new scale.
         */
        void SetActorScale(const Vector3& scale)
        { 
            mTransform.SetScale(scale);
        };

        /**
         * @brief Sets the scale of the actor using a 2D vector.
         * @param scale The new scale.
         */
        void SetActorScale(const Vector2& scale)
        {
            mTransform.SetScale(scale);
        };

        /**
         * @brief Sets the uniform scale of the actor.
         * @param scale The new scale value.
         */
        void SetActorScale(float scale) 
        { 
            mTransform.SetScale({scale, scale, scale});
        };

        /**
         * @brief Sets the rotation of the actor.
         * @param rot The new rotation as a quaternion.
         */
        void SetActorRotation(const Quaternion& rot)
        {
            mTransform.SetRotation(rot);
        }

        /**
         * @brief Sets the rotation of the actor using a float value.
         * @param rot The new rotation value.
         */
        void SetActorRotation(float rot)
        {
            mTransform.SetRotation(rot);
        }

        /**
         * @brief Sets the rotation of the actor using a vector (Euler angles).
         * @param rot The new rotation as Euler angles.
         */
        void SetActorRotation(const Vector3& rot)
        {
            mTransform.SetRotation(Quaternion::Concatenate(Quaternion::FromEuler(rot), Quaternion::Identity));
        }

        /**
         * @brief Sets the transform of the actor.
         * @param location The new location.
         * @param rotation The new rotation (Euler angles).
         * @param scale The new scale.
         */
        void SetActorTransform(const Vector3& location, const Vector3& rotation, const Vector3& scale)
        {
            mTransform.SetLocation(location);
            mTransform.SetRotation(rotation);
            mTransform.SetScale(scale);
        }

        /**
         * @brief Adds an offset to the actor's location.
         * @param locOffset The location offset.
         */
        void AddActorLocationOffset(const Vector3& locOffset) 
        { 
            mTransform.SetLocation(mTransform.Location() + locOffset);
        };

        /**
         * @brief Adds an offset to the actor's location using a 2D vector.
         * @param locOffset The location offset.
         */
        void AddActorLocationOffset(const Vector2& locOffset)
        {
            mTransform.SetLocation(mTransform.Location() + Vector3{locOffset.x, locOffset.y, 0});
        };

        /**
         * @brief Adds an offset to the actor's rotation.
         * @param rotOffset The rotation offset as a quaternion.
         */
        void AddActorRotationOffset(Quaternion rotOffset) 
        {
            mTransform.SetRotation(Quaternion::Concatenate(mTransform.Rotation(), rotOffset));
        };

        /**
         * @brief Adds an offset to the actor's rotation using a vector (Euler angles).
         * @param rotOffset The rotation offset.
         */
        void AddActorRotationOffset(Vector3 rotOffset)
        {
            if (rotOffset.Length() == 0) return;

            Quaternion increment(rotOffset.x * Timer::deltaTime, rotOffset.y * Timer::deltaTime, rotOffset.z * Timer::deltaTime, 1);

            mTransform.SetRotation(Quaternion::Concatenate(mTransform.Rotation(), increment));
        }

        /**
         * @brief Adds an offset to the actor's rotation using a float value.
         * @param rotOffset The rotation offset.
         */
        void AddActorRotationOffset(float rotOffset)
        {
            if (rotOffset == 0) return;

            Quaternion increment(mTransform.Rotation().x, mTransform.Rotation().y, rotOffset * Timer::deltaTime, 1);
            mTransform.SetRotation(Quaternion::Concatenate(mTransform.Rotation(), increment));
        }

        /**
         * @brief Gets the level the actor is attached to.
         * @return The level the actor is attached to.
         */
        Level* GetLevel() const { return mLevel; };

        friend Level;
    };

    /**
     * @brief Adds a component of type T to the actor.
     * @tparam T The type of the component to add (must derive from Component).
     * @tparam Args Constructor argument types for the component.
     * @param args Arguments to forward to the component's constructor.
     * @return Pointer to the newly added component, or nullptr if a component of this type already exists.
     */
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
