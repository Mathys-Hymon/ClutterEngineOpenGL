#include "pch.h"
#include <Core/CEngine.h>

using namespace clt;

void CEngine::Init(int pWidth, int pHeight, std::string pName)
{
	mWindow = std::make_unique<Window>(pWidth, pHeight, pName);
	mRenderer = std::make_unique<Renderer>();
}

void CEngine::Close()
{
	mWindow->Close();
}
