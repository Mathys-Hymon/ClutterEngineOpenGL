#pragma once
#include <Core/CCommon.h>
#include "Core/Maths/Color.h"

namespace clt
{
	enum class RendererType
	{
		OPENGL
	};

	class CEngine;
	class CLUTTER_API IRenderer
	{
	protected:
		bool mWireframe;
		Color mBackgroundColor;

	public:

		~IRenderer() = default;

		virtual void Initialize(CEngine* pEngine, Color backgroundColor) = 0;
		virtual void WireframeMode(bool wireframe) = 0;
		virtual void ToggleWireframe() = 0;
		virtual void BeginDraw() = 0;
		virtual void Draw() = 0;
		virtual void EndDraw() = 0;
		virtual void Close() = 0;
		virtual RendererType GetType() const = 0;
		virtual const CEngine* GetEngine() const = 0;

		virtual void AddMeshComponent(class MeshComponent* pComp) = 0;
		virtual void RemoveMeshComponent(class MeshComponent* pComp) = 0;
			
		virtual void AddSpriteComponent(class SpriteComponent* pComp) = 0;
		virtual void RemoveSpriteComponent(class SpriteComponent* pComp) = 0;

		virtual void AddHUDComponent(class HUDComponent* pComp) = 0;
		virtual void RemoveHUDComponent(class HUDComponent* pComp) = 0;
	};
}