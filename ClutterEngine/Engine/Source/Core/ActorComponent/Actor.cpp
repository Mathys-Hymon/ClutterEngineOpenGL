#include "pch.h"
#include <Core/ActorComponent/Actor.h>

Actor::Actor() : mState(ActorState::Active), mScene(nullptr)
{
}

Actor::~Actor()
{
}

void Actor::AddComponent(Component* pComponent)
{
	pComponent->mOwner = this;

	size_t hashCode = typeid(pComponent).hash_code();
	if (mComponents.find(hashCode) != mComponents.end()) CLUTTER_ERROR("A component of this type already exists in the Actor.")
	else mComponentsToAdd.push_back(pComponent);
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
	for (Component* pComponent : mComponentsByUpdateOrder)
	{
		if(pComponent->IsEnable()) pComponent->Update();
	}

		// Add new Components to actor
	for (Component* pComponent : mComponentsToAdd)
	{
		size_t hashCode = typeid(*pComponent).hash_code();
		mComponents[hashCode] = std::unique_ptr<Component>(pComponent);

		mComponentsByUpdateOrder.push_back(pComponent);
	}

		// Sort Components by Update order
	if (!mComponentsToAdd.empty())
	{
		std::sort(mComponentsByUpdateOrder.begin(), mComponentsByUpdateOrder.end(),
			[](Component* a, Component* b) {
				return a->GetUpdateOrder() < b->GetUpdateOrder();
			});
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
			mComponentsToRemove.emplace_back(pComponent);
		}
	}
}