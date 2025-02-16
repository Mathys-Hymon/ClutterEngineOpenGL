#pragma once
#include <Core/CCommon.h>
#include <Window/Window.h>
#include <Core/Levels/CLevelManager.h>
#include <Graphics/Renderer.h>

#include <memory>

namespace clt
{
	class CLUTTER_API CEngine
	{
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<Renderer> mRenderer;
		std::unique_ptr<CLevelManager> mLevelManager;
	public:
		CEngine() = default;
		~CEngine() = default;

		void Init(int pWidth, int pHeight, std::string pName, std::vector<CLevel*> pLevels);

		void Update();

		Window* GetWindow() const { return mWindow.get(); }
		Renderer* GetRenderer() const { return mRenderer.get(); }
		CLevelManager* GetLevelManager() const { return mLevelManager.get(); }
	};
}
