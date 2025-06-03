#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Shader/Shader.h>
#include <Core/Maths/CRectangle.h>
#include <Graphics/Shader/VertexArray.h>
#include <Core/ActorComponent/Components/Graphics/UI/HUDComponent.h>
#include <Graphics/IRenderer.h>

namespace clt
{
	class CEngine;
	class SpriteComponent;
	class MeshComponent;
	class TextElement;
	class ButtonElement;

  /**
  * @class RendererGL
  * @brief Responsible for rendering graphical components using OpenGL.
  */
	class CLUTTER_API RendererGL : public IRenderer
	{
		/**
   * @brief List of sprite components to render.
   */
		std::vector<SpriteComponent*> mSpriteComponents;

		/**
   * @brief List of mesh components to render.
   */
		std::vector<MeshComponent*> mMeshComponents;

		/**
   * @brief List of HUD components to render.
   */
		std::vector<HUDComponent*> mHUD;

		/**
   * @brief Shader program used for rendering sprites.
   */
		ShaderProgram mSpriteShader;

		/**
   * @brief Vertex array object for sprites.
   */
		VertexArray* mSpriteVAO;

		/**
   * @brief Shader program used for rendering text.
   */
		ShaderProgram mTextShader;

		/**
   * @brief UI view-projection matrix.
   */
		Matrix4Row mUiViewProj;

		/**
   * @brief Pointer to the engine instance.
   */
		CEngine* mEngine;

		friend TextElement;
		friend ButtonElement;

	public:
		/**
   * @brief Constructor for RendererGL.
   */
		RendererGL();

		/**
   * @brief Deleted copy constructor.
   */
		RendererGL(const RendererGL&) = delete;

		/**
   * @brief Destructor for RendererGL.
   */
		~RendererGL() = default;

		/**
   * @brief Deleted copy assignment operator.
   */
		RendererGL& operator=(const RendererGL&) = delete;

		/**
   * @brief Initializes the renderer with the engine and background color.
   * @param pEngine Pointer to the engine.
   * @param backgroundColor The background color to use.
   */
		void Initialize(CEngine* pEngine, Color backgroundColor) override;

		/**
   * @brief Closes the renderer and releases resources.
   */
		void Close() override;

		/**
   * @brief Enables or disables wireframe rendering mode.
   * @param wireframe True to enable wireframe mode, false to disable.
   */
		void WireframeMode(bool wireframe) override;

		/**
   * @brief Toggles the wireframe rendering mode.
   */
		void ToggleWireframe() override;

		/**
   * @brief Adds a mesh component to the renderer.
   * @param pComp Pointer to the mesh component.
   */
		void AddMeshComponent(MeshComponent* pComp);

		/**
   * @brief Removes a mesh component from the renderer.
   * @param pComp Pointer to the mesh component.
   */
		void RemoveMeshComponent(MeshComponent* pComp);

		/**
   * @brief Adds a sprite component to the renderer.
   * @param pComp Pointer to the sprite component.
   */
		void AddSpriteComponent(SpriteComponent* pComp);

		/**
   * @brief Removes a sprite component from the renderer.
   * @param pComp Pointer to the sprite component.
   */
		void RemoveSpriteComponent(SpriteComponent* pComp);

		/**
   * @brief Adds a HUD component to the renderer.
   * @param pComp Pointer to the HUD component.
   */
		void AddHUDComponent(HUDComponent* pComp);

		/**
   * @brief Removes a HUD component from the renderer.
   * @param pComp Pointer to the HUD component.
   */
		void RemoveHUDComponent(HUDComponent* pComp);
		
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

		/**
   * @brief Gets the engine associated with the renderer.
   * @return Pointer to the engine.
   */
		const CEngine* GetEngine() const override { return mEngine; };

		/**
   * @brief Gets the renderer type.
   * @return The renderer type (OpenGL).
   */
		const RendererType GetType() const override { return RendererType::OPENGL; }
	};
}
