#include "pch.h"                                      // Include precompiled header
#include <Core/ActorComponent/Actor.h>                // Include Actor header
#include <Core/ActorComponent/Component.h>
#include "Core/Levels/Level.h"
#include <Physics/IPhysics.h>

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

   mComponents.clear();                             // Clear all component containers
   mComponentsByUpdateOrder.clear();
   mComponentsToAdd.clear();
   mComponentsToRemove.clear();
}
bool Actor::LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, RaycastHit& outHit, const TraceParams& params)
{
    Actor* temp = nullptr;

    if (params.IgnoreActor) temp = this;

    return mLevel->GetPhysics().LineTrace(start, direction, maxDistance, outHit, params, temp);
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

   for (size_t hashCode : mComponentsToRemove)
   {
       auto it = mComponents.find(hashCode);
       if (it != mComponents.end())
       {
           Component* pComponent = it->second;

           auto itOrder = std::find(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(), pComponent);
           if (itOrder != mComponentsByUpdateOrder.end())
           {
               std::iter_swap(itOrder, mComponentsByUpdateOrder.end() - 1);
               mComponentsByUpdateOrder.pop_back();
           }

           delete pComponent;
           mComponents.erase(it);
       }
   }
   mComponentsToRemove.clear();
}
