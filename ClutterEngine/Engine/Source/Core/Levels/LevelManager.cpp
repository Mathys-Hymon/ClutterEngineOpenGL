#include "pch.h"
#include <Core/Levels/LevelManager.h>

using namespace clt;

LevelManager::LevelManager(std::vector<Level*>& pLevels, Renderer* pRenderer) : mActualLevel(pLevels[0]), mLevels({})
{
	for (Level* level : pLevels)
	{
		level->SetRenderer(pRenderer);
		mLevels.emplace(level->mTitle, level);
	}

	mActualLevel->Load();
}

LevelManager::~LevelManager()
{
	mActualLevel->Close();
	mActualLevel->Unload();

    for (auto& pair : mLevels)
    {
		delete pair.second;
    }
	mLevels.clear();
}

void LevelManager::Update()
{
	if(mActualLevel)	mActualLevel->InternalUpdate();
}
