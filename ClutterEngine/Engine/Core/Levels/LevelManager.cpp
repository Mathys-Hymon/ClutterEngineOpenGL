#include "pch.h"
#include <Core/Levels/LevelManager.h>
#include <Physics/Physics.h>

using namespace clt;

LevelManager::LevelManager(std::vector<Level*>& pLevels, RendererGL* pRenderer, Physics* pPhysics) : mActualLevel(pLevels[0]), mLevels({})
{
	for (Level* level : pLevels)
	{
		level->SetManager(pRenderer, pPhysics, this);
		mLevels.emplace(level->mTitle, level);
	}
	mActualLevel->Load();
}

LevelManager::~LevelManager()
{
	mActualLevel->Close();

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
		mActualLevel->Unload();
		mActualLevel = mLevelToLoad;
		mActualLevel->Load();

		mLevelToLoad = nullptr;
	}

	if(mActualLevel)	mActualLevel->InternalUpdate();
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
