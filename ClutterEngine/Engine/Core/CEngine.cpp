#include "pch.h"
#include <Core/CEngine.h>
#include <Input/Input.h>

using namespace clt;

void CEngine::Init(int pWidth, int pHeight, std::string pName, std::vector<Level*> pLevels)
{
	mWindow = std::make_unique<Window>(pWidth, pHeight, pName);
	mRenderer = std::make_unique<RendererGL>();
	mRenderer->Initialize(this);
	mPhysics = std::make_unique<Physics>();

	mLevelManager = std::make_unique<LevelManager>(pLevels, mRenderer.get(), mPhysics.get());
}

void CEngine::Update()
{
	mPhysics->Update();
	Input::Get().Update(mWindow.get());
	mLevelManager->Update();
}

void CEngine::Close()
{
	mRenderer->Close();
	mRenderer.release();
	mWindow.release();
	mPhysics.release();
}
