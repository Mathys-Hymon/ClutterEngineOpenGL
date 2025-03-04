#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Component.h>
#include <Graphics/UI/UIPanel.h>

namespace clt
{
	class CLUTTER_API HUDComponent : public Component
	{
		std::unordered_map<std::string, UIPanel*> mWidgets;
		UIPanel* mCurrentWidget;

	public:
		HUDComponent() : mCurrentWidget(nullptr), Component() {};
		~HUDComponent() = default;

		template<typename T, typename ...Args>
		T* CreateWidget(std::string pName, Args && ...args, bool mSetActive = false);

		template<typename T>
		T* GetWidget(const std::string pName);

		void ShowWidget(const std::string pName);

		void RemoveWidget(const std::string& pName);

		virtual void Update() override;
	};


	template<typename T, typename ...Args>
	inline T* HUDComponent::CreateWidget(std::string pName, Args && ...args, bool mSetActive)
	{
		static_assert(std::is_base_of<UIPanel, T>::value, "T must be a UIPanel");

		if (mWidgets.find(pName) != mWidgets.end())
		{
			CLUTTER_ERROR("An element of this name alreally exist");
			return nullptr;
		}
		else
		{
			T* pWidget = new T(std::forward<Args>(args)...);
			mWidgets[pName] = pWidget;

			if (mSetActive || !mCurrentWidget) mCurrentWidget = pWidget;

			return pWidget;
		}

		return nullptr;
	}

	template<typename T>
	inline T* HUDComponent::GetWidget(const std::string pName)
	{
		static_assert(std::is_base_of<UIPanel, T>::value, "T must be a UIPanel");

		auto it = mWidgets.find(pName);

		if (it != mWidgets.end())
		{
				return dynamic_cast<T*>(it->second);
		}
		return nullptr;
	}
}