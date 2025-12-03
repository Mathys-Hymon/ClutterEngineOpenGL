#include "pch.h"                                      // Include precompiled header
#include <Core/ActorComponent/Actor.h>                // Include Actor header
#include <Core/ActorComponent/Component.h>
#include "Core/Levels/Level.h"
#include <Physics/IPhysics.h>

#include "Core/Reflection/ObjectRegistry.h"

using namespace clt;                                  // Use clt namespace

// Constructor
Actor::Actor(Level* pLevel, std::string pName) :mLevel(pLevel), mState(ActorState::Active), mIsUpdatingComponents(false), mName(pName)
{
    SetupProperties();
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

void Actor::SetupProperties()
{
    Reflectable::SetupProperties();
}

nlohmann::json Actor::ToJson()
{
    nlohmann::json j = Reflectable::ToJson();
    
    j["Name"] = mName;
    
    j["Transform"]["Location"] = { mTransform.Location().x, mTransform.Location().y, mTransform.Location().z };
    j["Transform"]["Rotation"] = { mTransform.Rotation().x, mTransform.Rotation().y, mTransform.Rotation().z, mTransform.Rotation().w };
    j["Transform"]["Scale"] = { mTransform.Scale().x, mTransform.Scale().y, mTransform.Scale().z };
    
    nlohmann::json componentsArray = nlohmann::json::array();
    
    for (auto comp : mComponentsByUpdateOrder)
    {
        componentsArray.push_back(comp->ToJson());
    }
    j["Components"] = componentsArray;
    
    return j;
}

void Actor::FromJson(const nlohmann::json& j)
{
    Reflectable::FromJson(j);
    
    if (j.contains("Name")) mName = j["Name"];
    
    if (j.contains("Transform"))
    {
        
    }
    
    if (j.contains("Components"))
    {
        for (const auto& compJson : j["Components"])
        {
            std::string typeName = compJson["Type"];
            
            Component* newComp = ObjectRegistry::CreateComponent(typeName);
            
            if (newComp)
            {
                AddComponentInternal(newComp);
                newComp->SetOwner(this);
                
                newComp->FromJson(compJson);
                newComp->Start();
            }
            else
            {
                CLUTTER_ERROR("UNKNOWN ERROR WHEN LOADING COMPONENT " + typeName);
            }
        }
    }
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
