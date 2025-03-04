#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/Assets.h>
#include <Graphics/Shader/Shader.h>
#include <Core/Maths/CRectangle.h>
#include <Graphics/Shader/VertexArray.h>
#include <Graphics/IRenderer.h>

namespace clt
{
	class CEngine;
	class SpriteComponent;
	class MeshComponent;
	/**
  * @class Renderer
  * @brief Responsible for rendering graphical components.
  */
	class CLUTTER_API RendererGL : public IRenderer
	{
		std::vector<SpriteComponent*> mSpriteComponents;
		std::vector<MeshComponent*> mMeshComponents;

		Shader mUIShader;
		VertexArray* mUiVAO;

		Matrix4Row mUiViewProj;

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

		void AddMeshComponent(MeshComponent* pComp);
		void RemoveMeshComponent(MeshComponent* pComp);

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
