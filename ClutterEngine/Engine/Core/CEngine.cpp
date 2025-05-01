#include "pch.h"
#include <Core/CEngine.h>
#include <Input/Input.h>
#include "json/json.hpp"
#include <fstream>
#include <iostream>


using namespace clt;
using json = nlohmann::json;

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

	mWindow = std::make_unique<Window>(res[0], res[1], mName, config["render"]["vsync"]);
	mRenderer = std::make_unique<RendererGL>();
	mRenderer->Initialize(this, backgroundColor);
	mPhysics = std::make_unique<Physics>();

	mLevelManager = std::make_unique<LevelManager>(pLevels, mRenderer.get(), mPhysics.get());
	mRefreshFrameRate = 0;
}

void CEngine::Update()
{
mPhysics->Update();
Input::Get().Update(mWindow.get());
mLevelManager->Update();

if (isEditorMode())
{
	if (mRefreshFrameRate > 0.3f)
	{
        std::string temp = mName + "     |    FPS: " + std::to_string(static_cast<int>(1.0f / Timer::deltaTime));
		mWindow->RenameViewport(temp.c_str());
		mRefreshFrameRate = 0;
	}
	else
	{
		mRefreshFrameRate += Timer::deltaTime;
	}
}
}

void CEngine::Close()
{
	mRenderer->Close();
	mRenderer.release();
	mWindow.release();
	mPhysics.release();
}
