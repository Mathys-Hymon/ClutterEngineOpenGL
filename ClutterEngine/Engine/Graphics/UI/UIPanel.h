#pragma once
#include <Core/CCommon.h>
#include <unordered_map>

namespace clt
{
	class WidgetElement;
	class HUDComponent;

	/**
  * @brief Represents a UI panel that manages WidgetElements and their Z-ordering.
  */
	class CLUTTER_API UIPanel
	{
		std::unordered_map<std::string, WidgetElement*> mElementsByName; ///< Map of element names to WidgetElement pointers.
		std::vector<WidgetElement*> mElementsByZOrder; ///< Elements sorted by Z-order.

		HUDComponent* mHUD; ///< The HUD component that owns this panel.

		/**
   * @brief Updates the Z-order of a widget within the panel.
   * @param mWidget The widget whose order should be updated.
   */
		void UpdateWidgetOrder(WidgetElement* mWidget);

		friend WidgetElement;

	public:
		/**
   * @brief Constructs a UIPanel with the given HUD component.
   * @param hud The HUD component that owns this panel.
   */
		UIPanel(HUDComponent* hud) : mHUD(hud){};

		/**
   * @brief Destructor. Cleans up all WidgetElements.
   */
		~UIPanel();

		/**
   * @brief Creates a new WidgetElement of type T and adds it to the panel.
   * @tparam T The type of WidgetElement to create.
   * @tparam Args Constructor argument types for T.
   * @param pName The unique name for the element.
   * @param args Arguments to forward to the constructor of T.
   * @return Pointer to the created element, or nullptr if the name already exists.
   */
		template<typename T, typename... Args>
		T* CreateElement(const std::string& pName, Args&&... args);

		/**
   * @brief Retrieves a WidgetElement of type T by name.
   * @tparam T The type of WidgetElement to retrieve.
   * @param pName The name of the element.
   * @return Pointer to the element if found and of type T, nullptr otherwise.
   */
		template<typename T>
		T* GetElement(const std::string& pName);

		/**
   * @brief Removes a WidgetElement from the panel by name.
   * @param pName The name of the element to remove.
   */
		void RemoveElement(const std::string& pName);

		/**
   * @brief Updates the panel and its elements. Override to provide custom update logic.
   */
		virtual void Update();

		/**
   * @brief Gets the HUD component that owns this panel.
   * @return Pointer to the HUDComponent.
   */
		HUDComponent* GetHUD() const { return mHUD; };

		/**
   * @brief Gets all WidgetElements in the panel, sorted by Z-order.
   * @return Vector of WidgetElement pointers.
   */
		std::vector<WidgetElement*> GetElements() { return mElementsByZOrder; }
	};

	/**
  * @brief Template implementation for creating a WidgetElement of type T.
  */
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

	/**
  * @brief Template implementation for retrieving a WidgetElement of type T by name.
  */
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
