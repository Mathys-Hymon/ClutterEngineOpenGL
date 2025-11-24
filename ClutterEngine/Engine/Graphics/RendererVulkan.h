#pragma
#include "Core/CCommon.h"
#include <Graphics/IRenderer.h>

namespace clt
{
	class CLUTTER_API RendererVulkan : public IRenderer
	{
		
		Matrix4Row mUiViewProj;

		CEngine* mEngine;
		DebugDraw* mDebug;

	public:

		virtual void Initialize(CEngine* pEngine, Color backgroundColor) override;
		virtual void WireframeMode(bool wireframe) override;
		virtual void ToggleWireframe() override;
		virtual void BeginDraw() override;
		virtual void Draw() override;
		virtual void EndDraw() override;
		virtual void Close() override;

		const CEngine* GetEngine() const override { return mEngine; };

		RendererType GetType() const override { return RendererType::OPENGL; }

		DebugDraw* GetDebugDraw() const override { return mDebug; };


		virtual void AddMeshComponent(class MeshComponent* pComp) override;
		virtual void RemoveMeshComponent(class MeshComponent* pComp) override;

		virtual void AddSpriteComponent(class SpriteComponent* pComp) override;
		virtual void RemoveSpriteComponent(class SpriteComponent* pComp) override;

		virtual void AddHUDComponent(class HUDComponent* pComp) override;
		virtual void RemoveHUDComponent(class HUDComponent* pComp) override;
	};
}