#include "pch.h"
#include <Core/CEngine.h>
#include <Input/Inputs.h>
#include <Sound/Audio.h>
#include "json/json.hpp"
#include <fstream>
#include <iostream>
#include <Physics/Bullet/BulletPhysics.h>

using namespace clt;
using json = nlohmann::json;

std::unordered_map<std::string, std::function<std::unique_ptr<IPhysics>()>> physicsEngines;

CEngine::CEngine()
{
	physicsEngines =
	{
		//{ "Clutter", []() { return std::make_unique<ClutterPhysics>(); } },
		{ "Bullet", [this]() { return std::make_unique<BulletPhysics>(*this); } }
	};
}

void CEngine::Init(const std::string& path, std::vector<const std::string&> levelPath, std::vector<Level*> pLevels)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		CLUTTER_ERROR("Cannot load json config");
	}

	json config;
	file >> config;

	auto res = config["render"]["resolution"];
	auto color = config["render"]["backgroundColor"];
	Color backgroundColor = { color[0], color[1], color[2], color[3] };

	mName = config["project"]["name"];
	CLog::Init(mName);

	Window::Get().InternalInit(res[0], res[1], mName, config["render"]["vsync"]);

	mRenderer = std::make_unique<RendererGL>();
	mRenderer->Initialize(this, backgroundColor);

	std::string physic = config["physic"]["engine"];

	auto it = physicsEngines.find(physic);
	if (it != physicsEngines.end())
	{
		mPhysics = it->second();
	}
	else CLUTTER_ERROR("Unknown physics engine: " + physic);

	mLevelManager = std::make_unique<LevelManager>({levelPath}, mRenderer.get(), mPhysics.get());
	mRefreshFrameRate = 0;
}

void CEngine::Update()
{
	mPhysics->UpdatePhysics();

	Inputs::Get().Update();
	mLevelManager->Update();
	Audio::Get().Update();
}

void CEngine::Close()
{
	Audio::Get().Shutdown();
	mRenderer->Close();

	mRenderer.release();
	mPhysics.release();
}
