#include "pch.h"
#include <Core/ActorComponent/Actor.h>

using namespace clt;

Actor::Actor() : mState(ActorState::Active), mScene(nullptr), mIsUpdatingComponents(false)
{
}

Actor::~Actor()
{
	for (auto& pair : mComponents) {
		delete pair.second;
	}
	mComponents.clear();
	mComponentsByUpdateOrder.clear();
	mComponentsToAdd.clear();
	mComponentsToRemove.clear();
}

void Actor::AddComponent(Component* pComponent)
{
	size_t hashCode = typeid(pComponent).hash_code();

	if (mComponents.find(hashCode) != mComponents.end())
	{
		CLUTTER_ERROR("A component of this type already exists in the Actor.");
		delete pComponent;
	}
	else
	{
		pComponent->mOwner = this;

		if (mIsUpdatingComponents)	mComponentsToAdd.emplace_back(pComponent);
		else						AddComponentInternal(pComponent);
	}
}

void Actor::AddComponentInternal(Component* pComponent)
{
	size_t hashCode = typeid(*pComponent).hash_code();
	mComponents[hashCode] = pComponent;

	mComponentsByUpdateOrder.push_back(pComponent);

	std::sort(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(),
		[](Component* a, Component* b) {
			return a->GetUpdateOrder() < b->GetUpdateOrder();
		});
}

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

void Actor::InternalUpdate()
{
	Update();

		//Update Components
	mIsUpdatingComponents = true;
	for (Component* pComponent : mComponentsByUpdateOrder)
	{
		if(pComponent->IsEnable()) pComponent->Update();
	}
	mIsUpdatingComponents = false;

		// Add new Components to actor
	for (Component* pComponent : mComponentsToAdd)
	{
		AddComponentInternal(pComponent);
	}

	mComponentsToAdd.clear();

		//Delete Components
	for (Component* pComponent : mComponentsToRemove)
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
