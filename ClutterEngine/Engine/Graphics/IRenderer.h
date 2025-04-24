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

		virtual bool Initialize(CEngine* pEngine, Color backgroundColor) = 0;
		virtual void WireframeMode(bool wireframe) = 0;
		virtual void ToggleWireframe() = 0;
		virtual void BeginDraw() = 0;
		virtual void Draw() = 0;
		virtual void EndDraw() = 0;
		virtual void Close() = 0;
		const virtual RendererType GetType() const = 0;
		const virtual CEngine* GetEngine() const = 0;
	};
}