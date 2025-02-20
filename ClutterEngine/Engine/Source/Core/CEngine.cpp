#include "pch.h"
#include <Core/CEngine.h>
#include <Input/Input.h>

using namespace clt;

void CEngine::Init(int pWidth, int pHeight, std::string pName, std::vector<Level*> pLevels)
{
	mWindow = std::make_unique<Window>(pWidth, pHeight, pName);
	mRenderer = std::make_unique<Renderer>(this);

	mLevelManager = std::make_unique<LevelManager>(pLevels, mRenderer.get());
}

void CEngine::Update()
{
	Input::Get().Update(mWindow.get());
	mLevelManager->Update();
}
