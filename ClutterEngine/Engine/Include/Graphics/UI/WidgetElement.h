#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API WidgetElement
	{

	public:
		 WidgetElement() {};
		~WidgetElement() = default;

		void Update() {};
		virtual void Draw() = 0;
	};
}