#pragma once
#include <Core/CCommon.h>
#include <unordered_map>

namespace clt
{
	class WidgetElement;
	class CLUTTER_API UIPanel
	{
		std::unordered_map<std::string, WidgetElement*> mElementsByName;
		std::vector<WidgetElement*> mElementsByZOrder;

		void UpdateWidgetOrder(WidgetElement* mWidget);

		friend WidgetElement;

	public:

		template<typename T, typename... Args>
		T* CreateElement(const std::string& pName, Args&&... args);

		template<typename T>
		T* GetElement(const std::string& pName);

		void RemoveElement(const std::string& pName);

		virtual void Update();

		std::vector<WidgetElement*> GetElements() { return mElementsByZOrder; }
	};

	template<typename T, typename ...Args>
	inline T* UIPanel::CreateElement(const std::string& pName, Args && ...args)
	{
		static_assert(std::is_base_of<WidgetElement, T>::value, "T must be a WidgetElement");

		if (mElementsByName.find(pName) != mElementsByName.end())
		{
			CLUTTER_ERROR("An element of this name alreally exist");
			return nullptr;
		}
		else
		{
			T* pElement = new T(std::forward<Args>(args)...);

			pElement->SetOwner(this);
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

	template<typename T>
	inline T* UIPanel::GetElement(const std::string& pName)
	{
		static_assert(std::is_base_of<WidgetElement, T>::value, "T must be a WidgetElement");

		auto it = mElementsByName.find(pName);

		if (it != mElementsByName.end())
		{
			return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}
}