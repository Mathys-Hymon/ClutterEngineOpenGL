#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <vector>
#include <Window/Window.h>

namespace clt
{
	class GraphicComponent;
	/**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API Renderer
	{
		std::vector<GraphicComponent*> mComponents;
		Assets* mAssets;

	public:
		/**
   * @brief Constructor for Renderer.
   */
		Renderer();

		/**
   * @brief Deleted copy constructor.
   */
		Renderer(const Renderer&) = delete;

		~Renderer() {};
		/**
   * @brief Deleted copy assignment operator.
   */
		Renderer& operator=(const Renderer&) = delete;

		/**
   * @brief Adds a graphic component to the renderer.
   * @param pComp Pointer to the graphic component to add.
   */
		void AddGraphicComponent(GraphicComponent* pComp);

		/**
   * @brief Removes a graphic component from the renderer.
   * @param pComp Pointer to the graphic component to remove.
   */
		void RemoveGraphicComponent(GraphicComponent* pComp);
		
		/**
   * @brief Begins the drawing process.
   */
		void BeginDraw();

		/**
   * @brief Draws all added graphic components.
   */
		void Draw();

		/**
   * @brief Ends the drawing process.
   */
		void EndDraw();
	};
}
