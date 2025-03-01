#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/GraphicComponent.h>
#include <Graphics/UI/UIPanel.h>

namespace clt
{
	class CLUTTER_API HUDComponent : public GraphicComponent
	{
		std::unordered_map<std::string, UIPanel*> mWidgets;
		UIPanel* mCurrentWidget;

	public:
		HUDComponent() : mCurrentWidget(nullptr), GraphicComponent() {};
		~HUDComponent() = default;

		UIPanel* AddWidget(const std::string& pName, UIPanel* pWidget);
		void    AddWidgets(std::map<std::string, UIPanel*> pWidget);

		void ShowWidget(const std::string& pName);
		void ShowWidget(UIPanel* pWidget);

		void RemoveWidget(UIPanel* pWidget);
		void RemoveWidget(const std::string& pName);

		virtual void Draw(RendererGL& pRenderer) override;
		virtual void Update() override;
	};
}