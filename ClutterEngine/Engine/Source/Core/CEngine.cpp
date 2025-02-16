#include "pch.h"
#include <Core/CEngine.h>

using namespace clt;

void CEngine::Init(int pWidth, int pHeight, std::string pName, std::vector<CLevel*> pLevels)
{
	mWindow = std::make_unique<Window>(pWidth, pHeight, pName);
	mRenderer = std::make_unique<Renderer>();
	mLevelManager = std::make_unique<CLevelManager>(pLevels);
}

void CEngine::Update()
{
	mLevelManager->Update();
}
