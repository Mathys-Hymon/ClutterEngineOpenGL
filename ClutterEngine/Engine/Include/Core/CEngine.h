#pragma once
#include <Core/CCommon.h>
#include <Window/Window.h>
#include <Graphics/Renderer.h>

#include <memory>

namespace clt
{
	class CLUTTER_API CEngine
	{
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<Renderer> mRenderer;
	public:
		CEngine() = default;
		~CEngine() = default;

		void Init(int pWidth, int pHeight, std::string pName);
		void Close();

		Window* GetWindow() const { return mWindow.get(); }
		Renderer* GetRenderer() const { return mRenderer.get(); }
	};
}
