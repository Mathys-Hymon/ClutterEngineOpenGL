#pragma once
#include "InputData.h"
#include <unordered_map>
#include <functional>

namespace clt
{
	/**
  * @brief Class managing input actions and their states.
  */
	class CLUTTER_API Input
	{
		std::unordered_map<EKey, Action> mKeyActionMap;  /**< Map of key codes to actions */
		std::unordered_map<EKey, bool> mPreviousKeyStates;  /**< Map of previous key states */

		std::unordered_map<std::string, AxisMapping> mAxisMap;
		std::unordered_map<std::string, std::vector<std::function<void(float)>>> mAxisCallbacks;

		/**
   * @brief Default constructor.
   */
		Input() = default;

	public:
		/**
   * @brief Deleted copy constructor.
   */
		Input(const Input&) = delete;

		/**
   * @brief Deleted copy assignment operator.
   */
		Input& operator=(const Input&) = delete;

		/**
   * @brief Gets the singleton instance of the InputManager.
   * @return Reference to the singleton instance.
   */
		static Input& Get() {
			static Input instance;
			return instance;
		}

		/**
   * @brief Updates the state of the input manager.
   * @param pWindow Pointer to the GLFW window.
   */
		void Update(GLFWwindow* pWindow);

		/**
   * @brief Maps a key to an action.
   * @param pKey Key code.
   * @param pActionName Name of the action.
   * @param pState State of the input.
   */
		void MapKeyToAction(EKey pKey, const std::string& pActionName, EInputState pState);

		/**
   * @brief Registers a callback for an action.
   * @param pActionName Name of the action.
   * @param callback Function to be called when the action is triggered.
   */
		void RegisterActionCallback(const std::string& pActionName, std::function<void()> callback);

		void RegisterAxisCallback(const std::string& axisName, std::function<void(float)> callback);
		void MapKeysToAxis(EKey positiveKey, EKey negativeKey, const std::string& axisName);
	};
}