#include "pch.h"
#include <Core/Levels/Level.h>
#include "Physics/Physics.h"

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
		for (Actor* pActor : pair.second) 
		{
			if (pActor)
			{
				pActor->Destroy();
				delete pActor;
				pActor = nullptr;
			}
		}
	}
	mActors.clear();
}

bool Level::LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant)
{
	return mPhysics->LineTrace(start, direction, maxDistance, hit, debugPersistant);
}

void Level::UpdateActors()
{
	mUpdatingActors = true;
	for (auto& pair : mActors)
	{
		for (Actor* pActor : pair.second)
		{
			if (pActor->mState == ActorState::Active)
			{
				pActor->InternalUpdate();
			}
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
