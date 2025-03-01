#pragma once
#include <Core/CCommon.h>
#include <Graphics/UI/WidgetElement.h>

namespace clt
{
	class CLUTTER_API UIPanel
	{
		std::unordered_map<std::string, WidgetElement*> mWidgetsByName;
		std::vector<WidgetElement*> mWidgetByDrawOrder;

	public:

		template<typename T>

	};
}