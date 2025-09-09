#include "pch.h"
#include <Core/Levels/Level.h>
#include "Physics/Physics.h"
#include "Core/Levels/LevelManager.h"
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/ChildActors/EditorCamera.h>

using namespace clt;

Level::Level(std::string pTitle) : mTitle(pTitle), mRenderer(nullptr), mUpdatingActors(false), mManager(nullptr)
{
}

Level::~Level()
{
	Unload();
}

void Level::InternalUpdate()
{
	// Get the active camera
	CameraComponent* camera = CameraComponent::GetActiveCamera();
	if (!camera) AddActor<EditorCamera>();

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

bool Level::LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant, Actor* self)
{
	return mPhysics->LineTrace(start, direction, maxDistance, hit, debugPersistant, self);
}

void Level::OpenLevel(const std::string& pLevelName)
{
	mManager->LoadLevel(pLevelName);
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
