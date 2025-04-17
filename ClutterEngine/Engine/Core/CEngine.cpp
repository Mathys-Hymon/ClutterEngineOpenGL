#include "pch.h"
#include <Core/CEngine.h>
#include <Input/Input.h>

using namespace clt;

void CEngine::Init(int pWidth, int pHeight, std::string pName, std::vector<Level*> pLevels)
{
	mName = pName;
	mWindow = std::make_unique<Window>(pWidth, pHeight, pName);
	mRenderer = std::make_unique<RendererGL>();
	mRenderer->Initialize(this);
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
