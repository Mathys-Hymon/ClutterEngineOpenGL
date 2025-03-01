#pragma once
#include <Core/CCommon.h>
#include <Graphics/UI/WidgetElement.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API UIPanel
	{
		void UpdateWidgetOrder(WidgetElement* mWidget);

		friend WidgetElement;

	protected:
		std::unordered_map<std::string, WidgetElement*> mElementsByName;
		std::vector<WidgetElement*> mElementsByZOrder;

	public:

		template<typename T, typename... Args>
		T* CreateElement(std::string pName, Args&&... args);

		void Draw();
	};



	template<typename T, typename ...Args>
	inline T* UIPanel::CreateElement(std::string pName, Args && ...args)
	{
		if (mElementsByName.find(pName) != mElementsByName.end())
		{
			std::cerr << "An element of this name alreally exist\n";
			return nullptr;
		}
		else
		{
			T* pElement = new T(std::forward<Args>(args)...);
			mElementsByName[pName] = pElement;

			auto it = std::lower_bound(mElementsByZOrder.begin(), mElementsByZOrder.end(), pElement,
				[](const auto& a, const auto& b) 
				{
					return a->GetZOrder() < b->GetZOrder();
				});
			mElementsByZOrder.insert(it, std::move(pElement));
			return pElement;
		}
	}
}