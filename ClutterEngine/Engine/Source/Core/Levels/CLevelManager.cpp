#include "pch.h"
#include <Core/Levels/CLevelManager.h>

using namespace clt;

CLevelManager::CLevelManager(std::vector<CLevel*>& pLevels) : mActualLevel(pLevels[0]), mLevels({})
{
	for (CLevel* level : pLevels)
	{
		mLevels.emplace(level->mTitle, level);
	}

	mActualLevel->Load();
}

CLevelManager::~CLevelManager()
{
	mActualLevel->Close();
	mActualLevel->Unload();

    for (auto& pair : mLevels)
    {
		delete pair.second;
    }
	mLevels.clear();
}

void CLevelManager::Update()
{
	if(mActualLevel)	mActualLevel->InternalUpdate();
}
