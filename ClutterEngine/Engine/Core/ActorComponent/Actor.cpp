#include "pch.h"                                      // Include precompiled header
#include <Core/ActorComponent/Actor.h>                // Include Actor header
#include <Core/ActorComponent/Component.h>

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
   mComponents.clear();                             // Clear all component containers
   mComponentsByUpdateOrder.clear();
   mComponentsToAdd.clear();
   mComponentsToRemove.clear();
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

   auto it = std::lower_bound(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), pComponent, 
       [](const auto& a, const auto& b) {
           return a->GetUpdateOrder() < b->GetUpdateOrder();
       });

   mComponentsByUpdateOrder.insert(it, std::move(pComponent));
   pComponent->SetOwner(this);
}

// Remove a component from the actor
template<typename T>
inline void Actor::RemoveComponent()
{
   static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

   size_t hashCode = typeid(T).hash_code();
   auto it = mComponents.find(hashCode);
   if (it != mComponents.end()) 
   {
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

       if (it != mComponentsByUpdateOrder.end()) 
       {
           std::iter_swap(it, mComponentsByUpdateOrder.end() - 1);
           mComponentsByUpdateOrder.pop_back();
       }

       size_t hashCode = typeid(*pComponent).hash_code();
       
       auto comp = mComponents.find(hashCode);
       delete comp->second;
       mComponents.erase(comp);
   }
}
