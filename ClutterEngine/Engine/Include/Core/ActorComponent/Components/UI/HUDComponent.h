#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/GraphicComponent.h>
#include <Core/ActorComponent/Components/UI/WidgetComponent.h>

namespace clt
{
	class CLUTTER_API HUDComponent : public GraphicComponent
	{
		std::map<std::string, WidgetComponent*> mWidgets;
	public:
		HUDComponent() : GraphicComponent() {};
		~HUDComponent() = default;

		void AddWidget(const std::string& pName, WidgetComponent* pWidget);
		void AddWidget(std::map<std::string, WidgetComponent*> pWidget);

		void RemoveWidget(WidgetComponent* pWidget);
		void RemoveWidget(const std::string& pName);

		virtual void Draw(RendererGL& pRenderer) override;
		virtual void Update() override;
	};
}