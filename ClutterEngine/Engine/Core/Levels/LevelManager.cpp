#include "pch.h"
#include <Core/Levels/LevelManager.h>
#include <Sound/Audio.h>
#include <Physics/Physics.h>

using namespace clt;

LevelManager::LevelManager(std::vector<Level*>& pLevels, RendererGL* pRenderer, Physics* pPhysics) : mCurrentLevel(pLevels[0]), mLevels({})
{
	for (Level* level : pLevels)
	{
		level->SetManager(pRenderer, pPhysics, this);
		mLevels.emplace(level->mTitle, level);
	}
	mCurrentLevel->Load();
}

LevelManager::~LevelManager()
{
	mCurrentLevel->Close();

    for (auto& pair : mLevels)
    {
		delete pair.second;
    }
	mLevels.clear();
}

void LevelManager::Update()
{
	if (mLevelToLoad)
	{
		mCurrentLevel->Unload();
		Audio::Get().ClearSpawnedSounds();
		mCurrentLevel = mLevelToLoad;
		mCurrentLevel->Load();

		mLevelToLoad = nullptr;
	}

	if(mCurrentLevel)	mCurrentLevel->InternalUpdate();
}

void LevelManager::LoadLevel(const std::string& levelName)
{
	auto* newLevel = mLevels[levelName];

	if (!newLevel)
	{
		CLUTTER_WARNING("Cannot find level : " + levelName);
		return;
	}
	else
	{
		mLevelToLoad = newLevel;
	}
}
