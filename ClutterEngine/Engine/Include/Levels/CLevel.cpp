#include "pch.h"
#include "CLevel.h"

using namespace clt;

CLevel::CLevel(std::string pTitle) : mTitle(pTitle), mRenderer(nullptr)
{
}

CLevel::~CLevel()
{
}

void CLevel::InternalUpdate()
{
	UpdateActors();
	Update();
}

void CLevel::Unload()
{
	for (auto& pair : mActors) {
		for (Actor* pActor : pair.second) {
			delete pActor;
		}
	}
	mActors.clear();
}

void CLevel::AddActor(Actor* pActor)
{
	if (!pActor) CLUTTER_ERROR("Cannot add a null Actor.");

	if (mUpdatingActors)
	{
		mPendingActors.push_back(pActor);
	}
	else
	{
		size_t hashCode = typeid(*pActor).hash_code();

		mActors[hashCode].push_back(pActor);
	}
}

void CLevel::RemoveActor(Actor* pActor)
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

void CLevel::UpdateActors()
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
	}

	for (Actor* pActor : mDeadActors)
	{
		delete pActor;
	}
}
