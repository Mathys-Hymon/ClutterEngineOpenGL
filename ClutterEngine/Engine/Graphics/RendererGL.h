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
		VertexArray* mTextVAO;

		Matrix4Row mUiViewProj;

		CEngine* mEngine;

		friend TextElement;
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

		void WireframeMode(bool wireframe) override;
		void ToggleWireframe() override;

		void AddMeshComponent(MeshComponent* pComp);
		void RemoveMeshComponent(MeshComponent* pComp);

		void AddSpriteComponent(SpriteComponent* pComp);
		void RemoveSpriteComponent(SpriteComponent* pComp);

		void AddHUDComponent(HUDComponent* pComp);
		void RemoveHUDComponent(HUDComponent* pComp);
		
		/**
   * @brief Begins the drawing process.
   */
		void BeginDraw() override;

		/**
   * @brief Draws all added graphic components.
   */
		void Draw() override;

		void BindText(Color textColor = Color::white);
		/**
   * @brief Ends the drawing process.
   */
		void EndDraw() override;

		const CEngine* GetEngine() const override { return mEngine; };

		const RendererType GetType() const override { return RendererType::OPENGL; }
	};
}
