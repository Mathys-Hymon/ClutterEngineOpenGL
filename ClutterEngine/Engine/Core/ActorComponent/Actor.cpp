#include "pch.h"                                      // Include precompiled header
#include <Core/ActorComponent/Actor.h>                // Include Actor header
#include <Core/ActorComponent/Component.h>
#include "Core/Levels/Level.h"

using namespace clt;                                  // Use clt namespace

// Constructor
Actor::Actor(Level* pLevel, std::string pName) :mLevel(pLevel), mState(ActorState::Active), mIsUpdatingComponents(false), mName(pName)
{
}

// Destructor
Actor::~Actor()
{
   for (auto& pair : mComponents) {                 // Delete all components
       delete pair.second;
   }

   for (auto& comp : mComponentsToAdd)
   {
       delete comp;
   }

   for (auto& comp : mComponentsToRemove)
   {
       delete comp;
   }

   mComponents.clear();                             // Clear all component containers
   mComponentsByUpdateOrder.clear();
   mComponentsToAdd.clear();
   mComponentsToRemove.clear();
}
bool Actor::LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant, bool ignoreSelf)
{
    Actor* temp = nullptr;

    if (ignoreSelf) temp = this;

    return mLevel->LineTrace(start, direction, maxDistance, hit, debugPersistant, temp);
}

// Internal method to add a component
void Actor::AddComponentInternal(Component* pComponent)
{
   size_t hashCode = typeid(*pComponent).hash_code();
   mComponents[hashCode] = pComponent;

   auto it = std::lower_bound(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), pComponent, 
       [](const auto& a, const auto& b) {
           return a->GetUpdateOrder() < b->GetUpdateOrder();
       });

   mComponentsByUpdateOrder.insert(it, std::move(pComponent));
   pComponent->SetOwner(this);
}

// Internal update method
void Actor::InternalUpdate()
{
   Update();                                        // Update the actor

   mIsUpdatingComponents = true;                    // Update components
   for (Component* pComponent : mComponentsByUpdateOrder)
   {
       if(pComponent->IsActive()) pComponent->Update();
   }
   mIsUpdatingComponents = false;

   for (Component* pComponent : mComponentsToAdd)   // Add new components to actor
   {
       AddComponentInternal(pComponent);
   }

   mComponentsToAdd.clear();

   for (Component* pComponent : mComponentsToRemove) // Delete components
   {
       std::vector<Component*>::iterator it = std::find(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), pComponent);

       size_t hashCode = typeid(*pComponent).hash_code();

       if (it != mComponentsByUpdateOrder.end())
       {
           std::iter_swap(it, mComponentsByUpdateOrder.end() - 1);
           mComponentsByUpdateOrder.pop_back();
       }
       auto comp = mComponents.find(hashCode);
       delete comp->second;
       mComponents.erase(comp);
   }
}
