#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Shader.h>
#include <Core/Maths/CRectangle.h>
#include <unordered_set>
#include <vector>
#include <Window/Window.h>

namespace clt
{
	class SpriteComponent;
	class GraphicComponent;
	/**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API Renderer
	{
		std::unordered_set<Texture*> mBindedTextures;
		std::vector<GraphicComponent*> mComponents;

		GLuint mVAO, mVBO, mAttribSize;
		std::vector<GLfloat> mBuffers;
		Shader mShader;

	public:
		/**
   * @brief Constructor for Renderer.
   */
		Renderer();

		/**
   * @brief Deleted copy constructor.
   */
		Renderer(const Renderer&) = delete;

		~Renderer();
		/**
   * @brief Deleted copy assignment operator.
   */
		Renderer& operator=(const Renderer&) = delete;

		void RegisterTextureUsage(Texture* pTexture);

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

		void DrawSprite(const class Actor& pActor, const class Texture& pTexture, CRectangle pRect, Vector2 pOrigin) const;

		/**
   * @brief Ends the drawing process.
   */
		void EndDraw();
	};
}
