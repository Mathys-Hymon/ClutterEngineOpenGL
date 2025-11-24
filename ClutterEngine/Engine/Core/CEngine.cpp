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
std::unordered_map<std::string, std::function<std::unique_ptr<IRenderer>()>> rendererEngines;

CEngine::CEngine()
{
	physicsEngines =
	{
		//{ "Clutter", []() { return std::make_unique<ClutterPhysics>(); } },
		{ "Bullet", [this]() { return std::make_unique<BulletPhysics>(*this); } }
	};

	rendererEngines =
	{
		{ "OpenGL", [this]() { return std::make_unique<RendererGL>(); } }
		//{ "Vulkan", [this]() { return std::make_unique<BulletPhysics>(); } }
	};
}

void CEngine::Init(const std::string& path, std::vector<Level*> pLevels)
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


	std::string renderer = config["render"]["engine"];

	auto rendererIt = rendererEngines.find(renderer);
	if (rendererIt != rendererEngines.end())
	{
		mRenderer = rendererIt->second();
		mRenderer->Initialize(this, backgroundColor);
	}
	else CLUTTER_ERROR("Unknown rendering engine: " + renderer);

	std::string physic = config["physic"]["engine"];

	auto physicsIt = physicsEngines.find(physic);
	if (physicsIt != physicsEngines.end())
	{
		mPhysics = physicsIt->second();
	}
	else CLUTTER_ERROR("Unknown physics engine: " + physic);

	mLevelManager = std::make_unique<LevelManager>(pLevels, mRenderer.get(), mPhysics.get());
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
