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
	class DebugDraw;
	class CEngine;
	class SpriteComponent;
	class MeshComponent;
	class TextElement;
	class ButtonElement;

  /**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API RendererGL : public IRenderer
	{
		std::vector<SpriteComponent*> mSpriteComponents;
		std::vector<MeshComponent*> mMeshComponents;
		std::vector<HUDComponent*> mHUD;

		ShaderProgram mSpriteShader;
		VertexArray* mSpriteVAO;

		ShaderProgram mTextShader;

		Matrix4Row mUiViewProj;

		CEngine* mEngine;
		DebugDraw* mDebug;

		friend TextElement;
		friend ButtonElement;

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

		void Initialize(CEngine* pEngine, Color backgroundColor) override;

		void Close() override;

		void WireframeMode(bool wireframe) override;
		void ToggleWireframe() override;

		void AddMeshComponent(MeshComponent* pComp) override;
		void RemoveMeshComponent(MeshComponent* pComp) override;

		void AddSpriteComponent(SpriteComponent* pComp) override;
		void RemoveSpriteComponent(SpriteComponent* pComp) override;

		void AddHUDComponent(HUDComponent* pComp) override;
		void RemoveHUDComponent(HUDComponent* pComp) override;
		
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

		RendererType GetType() const override { return RendererType::OPENGL; }

		DebugDraw* GetDebugDraw() const override { return mDebug; };
	};
}
