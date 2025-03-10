#include "pch.h"
#include <Core/Levels/Level.h>

using namespace clt;

Level::Level(std::string pTitle) : mTitle(pTitle), mRenderer(nullptr), mUpdatingActors(false)
{
}

Level::~Level()
{
	Unload();
}

void Level::InternalUpdate()
{
	UpdateActors();
	Update();
}

void Level::Unload()
{
	for (auto& pair : mActors) {
		for (Actor* pActor : pair.second) {
			delete pActor;
		}
	}
	mActors.clear();
}

Actor* Level::AddActor(Actor* pActor)
{
	if			(!pActor) CLUTTER_ERROR("Cannot add a null Actor.")
	else
	{
		pActor->AttachLevel(this);

		if (mUpdatingActors)
		{
			mPendingActors.emplace_back(pActor);
		}
		else
		{
			size_t hashCode = typeid(*pActor).hash_code();

			mActors[hashCode].emplace_back(pActor);

            size_t lastIndex = mActors[hashCode].size() - 1;
            return mActors[hashCode][lastIndex];
		}
	}
}

void Level::RemoveActor(Actor* pActor)
{
	if (!pActor) CLUTTER_ERROR("Cannot remove a null Actor.");
	size_t typeHash = typeid(pActor).hash_code();

	auto& actors = mActors[typeHash];
	auto it = std::find(actors.begin(), actors.end(), pActor);

	if(it == actors.end()) CLUTTER_ERROR(mTitle + " has no actor of type: " + typeid(*pActor).name())
	else 
	{
		delete* it;
		actors.erase(it);
	}
}

void Level::UpdateActors()
{
	mUpdatingActors = true;
	for (auto& pair : mActors)
	{
		for (Actor* pActor : pair.second)
		{
			pActor->InternalUpdate();
		}
	}
	mUpdatingActors = false;

	for (Actor* pActor : mPendingActors)
	{
		size_t typeHash = typeid(pActor).hash_code();
		mActors[typeHash].push_back(pActor);
		pActor->mLevel = this;
	}
	mPendingActors.clear();

	for (Actor* pActor : mDeadActors)
	{
		delete pActor;
	}
	mDeadActors.clear();
}
