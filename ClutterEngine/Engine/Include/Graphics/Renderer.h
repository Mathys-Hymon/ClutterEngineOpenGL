#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Shader.h>
#include <Core/Maths/CRectangle.h>
#include <Graphics/Sprite/SpriteBatch.h>
#include <unordered_map>
#include <vector>

namespace clt
{
	class CEngine;
	class SpriteComponent;
	class GraphicComponent;
	/**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API Renderer
	{
		//std::unordered_set<Texture*> mBindedTextures;
		std::unordered_map<Texture*, SpriteBatch*> mSpriteBatches;
		std::vector<GraphicComponent*> mComponents;

		GLuint mVAO, mVBO, mAttribSize;
		std::vector<GLfloat> mBuffers;
		Shader mShader;

		CEngine& mEngine;

	public:
		/**
   * @brief Constructor for Renderer.
   */
		Renderer(CEngine* pEngine);

		/**
   * @brief Deleted copy constructor.
   */
		Renderer(const Renderer&) = delete;

		~Renderer();
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

		void AddSpriteComponent(SpriteComponent* pComp);

		void RemoveSpriteComponent(SpriteComponent* pComp);
		
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

		const CEngine& GetEngine() const { return mEngine; };
	};
}
