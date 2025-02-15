#pragma once
#include <Core/CCommon.h>
#include <Window/Window.h>

namespace clt
{
	class GraphicComponent;
	class CLUTTER_API Renderer
	{
	public:
		Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		bool Initialize(Window& pWindow);

		void AddGraphicComponent(GraphicComponent* pComp);
		void RemoveGraphicComponent(GraphicComponent* pComp);
		
		void BeginDraw();
		void Draw();
		void EndDraw();


	private:
	};
}
