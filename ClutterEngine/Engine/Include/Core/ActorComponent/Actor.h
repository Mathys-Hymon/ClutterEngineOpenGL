#pragma once
#include "Component.h"
#include <Core/Maths/Transforms/Transform2D.h>
#include <unordered_map>
#include <vector>


enum class ActorState {
    Active,
    Paused,
    Dead
};

namespace clt
{
    class CLevel;
    class CLUTTER_API Actor
    {

        void InternalUpdate();
        void AddComponentInternal(Component* pComponent);

        bool mIsUpdatingComponents;

    protected:
        ActorState mState; ///< The state of the actor.
        CLevel* mScene; ///< The scene the actor is attached to.
        Transform2D mTransform;

        std::unordered_map<size_t, Component*> mComponents;
        std::vector<Component*> mComponentsByUpdateOrder;
        std::vector<Component*> mComponentsToAdd;
        std::vector<Component*> mComponentsToRemove;

    public:
        Actor();
        ~Actor();

        virtual void Update() {};

        void AddComponent(Component* pComponent);

        template<typename T>
        void RemoveComponent();

        void AttachScene(CLevel* pScene) { mScene = pScene; };

        Transform2D getTransform() const { return mTransform; };
        Vector2 GetPosition() const { return mTransform.location; };
        Vector2 GetScale() const { return mTransform.scale; };

        virtual void OnCollision(Actor* other) {};
        virtual void OnCollisionEnd(Actor* other) {};

        void SetActorLocation(Vector2 loc) { mTransform.location = loc; };
        void SetActorScale(Vector2 scale) { mTransform.scale = scale; };
        void SetActorRotation(float rot) { mTransform.rotation = rot; };

        void AddActorLocationOffset(Vector2 locOffset) { mTransform.location += locOffset; };
        void AddActorRotationOffset(float rotOffset) { mTransform.rotation += rotOffset; };

        CLevel& GetScene() const { return *mScene; };

        friend CLevel;

    };
}


