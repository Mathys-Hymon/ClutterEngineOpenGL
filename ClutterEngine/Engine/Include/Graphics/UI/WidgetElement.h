#pragma once
#include <Core/CCommon.h>

namespace clt
{
	UIPanel;
	class CLUTTER_API WidgetElement
	{
		int mZOrder;
		UIPanel* mOwner;

		void SetOwner(UIPanel* pOwner) { mOwner = pOwner; };

		friend UIPanel;
	public:

		bool mVisibility;

		 WidgetElement(int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr) {};
		~WidgetElement() = default;

		virtual void Update() {};
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

		void ToggleVisibility() { mVisibility = !mVisibility; };
	};
}