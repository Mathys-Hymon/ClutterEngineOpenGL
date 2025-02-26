#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Shader.h>
#include <Core/Maths/CRectangle.h>
#include <Graphics/Sprite/SpriteBatch.h>
#include <Graphics/IRenderer.h>

namespace clt
{
	class CEngine;
	class SpriteComponent;
	class GraphicComponent;
	/**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API RendererGL : IRenderer
	{
		//std::unordered_set<Texture*> mBindedTextures;
		std::unordered_map<Texture*, SpriteBatch*> mSpriteBatches;
		std::vector<GraphicComponent*> mComponents;

		GLuint mVAO, mVBO, mAttribSize;
		std::vector<GLfloat> mBuffers;
		Shader mShader;
		CEngine* mEngine;

	public:
		/**
   * @brief Constructor for Renderer.
   */
		RendererGL();

		/**
   * @brief Deleted copy constructor.
   */
		RendererGL(const RendererGL&) = delete;

		~RendererGL() = default;
		/**
   * @brief Deleted copy assignment operator.
   */
		RendererGL& operator=(const RendererGL&) = delete;

		bool Initialize(CEngine* pEngine) override;

		void Close() override;

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
		void BeginDraw() override;

		/**
   * @brief Draws all added graphic components.
   */
		void Draw() override;

		/**
   * @brief Ends the drawing process.
   */
		void EndDraw() override;

		const CEngine* GetEngine() const override { return mEngine; };

		const RendererType GetType() const override { return RendererType::OPENGL; }
	};
}
