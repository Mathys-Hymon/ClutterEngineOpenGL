#pragma once
#include <Core/CCommon.h>
#include <GLFW/glfw3.h>
#include <Window/Window.h>

namespace clt
{
	class CLUTTER_API Renderer
	{
	public:
		Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		bool Initialize(Window& pWindow);

		void BeginDraw();
		void Draw();
		void EndDraw();


	private:
		
	};
}
