#pragma once
#include <GLFW/glfw3.h>
#include <Window/Window.h>

namespace clt
{
	class Renderer
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
