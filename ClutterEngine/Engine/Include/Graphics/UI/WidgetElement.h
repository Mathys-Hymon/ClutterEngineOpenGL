#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class UIPanel;
	class CLUTTER_API WidgetElement
	{
		int mZOrder;
		UIPanel* mOwner;

	public:
		 WidgetElement(int ZOrder = 0) : mZOrder(ZOrder) {};
		~WidgetElement() = default;

		void Update() {};
		virtual void Draw() = 0;

		int GetZOrder() const { return mZOrder; };
		void SetZOrder(int ZOrder)
		{
			if (ZOrder != mZOrder)
			{
				mZOrder = ZOrder;
				mOwner->UpdateWidgetOrder(this);
			}
		}
	};
}