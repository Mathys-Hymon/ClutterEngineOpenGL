#pragma once
#include <Core/CCommon.h>

namespace clt
{
	enum class RendererType
	{
		OPENGL
	};

	class CEngine;
	class CLUTTER_API IRenderer
	{
	public:

		~IRenderer() = default;

		virtual bool Initialize(CEngine* pEngine) = 0;
		virtual void WireframeMode(bool wireframe) = 0;
		virtual void BeginDraw() = 0;
		virtual void Draw() = 0;
		virtual void EndDraw() = 0;
		virtual void Close() = 0;
		const virtual RendererType GetType() const = 0;
		const virtual CEngine* GetEngine() const = 0;
	};
}