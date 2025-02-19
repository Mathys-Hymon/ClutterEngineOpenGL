#include "pch.h"                                      // Include precompiled header
#include <Core/ActorComponent/Actor.h>                // Include Actor header

using namespace clt;                                  // Use clt namespace

// Constructor
Actor::Actor(std::string pName = "Actor") : mState(ActorState::Active), mLevel(nullptr), mIsUpdatingComponents(false), mName(pName)
{
}

// Destructor
Actor::~Actor()
{
   for (auto& pair : mComponents) {                 // Delete all components
       delete pair.second;
   }
   mComponents.clear();                             // Clear all component containers
   mComponentsByUpdateOrder.clear();
   mComponentsToAdd.clear();
   mComponentsToRemove.clear();
}

// Add a component to the actor
void Actor::AddComponent(Component* pComponent)
{
   size_t hashCode = typeid(*pComponent).hash_code();

   if (mComponents.find(hashCode) != mComponents.end())
   {
       CLUTTER_ERROR("A component of this type already exists in the Actor.");
       delete pComponent;
   }
   else
   {
       if (mIsUpdatingComponents) mComponentsToAdd.emplace_back(pComponent);
       else AddComponentInternal(pComponent);
   }
}

void clt::Actor::AttachLevel(Level* pLevel)
{
    mLevel = pLevel;
}

// Internal method to add a component
void Actor::AddComponentInternal(Component* pComponent)
{
   size_t hashCode = typeid(*pComponent).hash_code();
   mComponents[hashCode] = pComponent;

   pComponent->SetOwner(this);

   mComponentsByUpdateOrder.push_back(pComponent);

   std::sort(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), // Sort components by update order
       [](Component* a, Component* b) {
           return a->GetUpdateOrder() < b->GetUpdateOrder();
       });
}

// Remove a component from the actor
template<typename T>
inline void Actor::RemoveComponent()
{
   static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

   size_t hashCode = typeid(T).hash_code();
   auto it = mComponents.find(hashCode);
   if (it != mComponents.end()) {
       mComponentsToRemove.push_back(it->second.get());
   }
}

// Internal update method
void Actor::InternalUpdate()
{
   Update();                                        // Update the actor

   mIsUpdatingComponents = true;                    // Update components
   for (Component* pComponent : mComponentsByUpdateOrder)
   {
       if(pComponent->IsEnable()) pComponent->Update();
   }
   mIsUpdatingComponents = false;

   for (Component* pComponent : mComponentsToAdd)   // Add new components to actor
   {
       AddComponentInternal(pComponent);
   }

   mComponentsToAdd.clear();

   for (Component* pComponent : mComponentsToRemove) // Delete components
   {
       size_t hashCode = typeid(*pComponent).hash_code();
       mComponents.erase(hashCode);

       std::vector<Component*>::iterator it = std::find(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), pComponent);

       if (it != mComponentsByUpdateOrder.end()) 
       {
           std::iter_swap(it, mComponentsByUpdateOrder.end() - 1);
           mComponentsByUpdateOrder.pop_back();
       }
   }
}
