#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CEngine;
	class CLUTTER_API IRenderer
	{
	public:
		enum class RendererType
		{
			OPENGL
		};

		~IRenderer() = default;

		virtual bool Initialize(CEngine* pEngine) = 0;
		virtual void BeginDraw() = 0;
		virtual void Draw() = 0;
		virtual void EndDraw() = 0;
		virtual void Close() = 0;
		const virtual RendererType GetType() const = 0;
		const virtual CEngine* GetEngine() const = 0;
	};
}