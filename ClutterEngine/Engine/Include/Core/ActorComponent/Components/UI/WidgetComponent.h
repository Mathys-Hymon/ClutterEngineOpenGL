#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/GraphicComponent.h>

namespace clt
{
	class CLUTTER_API WidgetComponent : public GraphicComponent
	{

	public:
		 WidgetComponent() : GraphicComponent() {};
		~WidgetComponent() = default;

		virtual void Draw(RendererGL& pRenderer) override = 0;
	};
}