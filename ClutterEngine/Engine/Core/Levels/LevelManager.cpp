#include "pch.h"
#include <Core/Levels/LevelManager.h>
#include <Sound/Audio.h>

#include "Core/JsonUtility.h"

using namespace clt;

LevelManager::LevelManager(std::vector<const std::string&> pLevelsPath, std::vector<Level*>& pLevels, IRenderer* pRenderer, IPhysics* pPhysics) : mLevelsPath({}), mCurrentLevel(pLevels[0])
{
	mCurrentLevel->SetManager(pRenderer, pPhysics, this);
	for (const std::string& levelPath : pLevelsPath)
	{
		nlohmann::json j;
		if (!JsonUtility::LoadFromFile(levelPath, j)) continue;
		
		mLevelsPath[j["Title"]] = levelPath;
	}
	
	mCurrentLevel->Load();
	
	LoadLevel(pLevelsPath[0]);
}

LevelManager::~LevelManager()
{
	mCurrentLevel->Close();

    for (auto& pair : mLevelsPath)
    {
		delete pair.second;
    }
	mLevelsPath.clear();
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

void LevelManager::SaveLevel(const std::string& filePath)
{
	nlohmann::json j;
	j["Title"] = mCurrentLevel->mTitle;
	
	nlohmann::json actorArray = nlohmann::json::array();
	
	auto actors = mCurrentLevel->GetAllActors();
	
	for (auto* actor : actors)
	{
		actorArray.push_back(actor->ToJson());
	}
	
	j["Actors"] = actorArray;
	
	JsonUtility::SaveToFile(filePath, j);
}

bool LevelManager::LoadLevel(const std::string& filePath)
{
	nlohmann::json j;
	if (!JsonUtility::LoadFromFile(filePath, j))
	{
		if (!JsonUtility::LoadFromFile(mLevelsPath[filePath], j)) return false;
	}
	
	Level* newLevel = new Level(j["Title"]);
	
	if (j.contains("Actors") && j["Actors"].is_array())
	{
		for (const auto& actorJson : j["Actors"])
		{
			auto newActor = newLevel->AddActor<Actor>();
			newActor->FromJson(actorJson);
		}
	}
	
	return true;
}
