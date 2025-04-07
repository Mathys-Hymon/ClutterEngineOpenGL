#pragma once
#include "InputData.h"
#include <unordered_map>
#include <Window/Window.h>
#include <functional>

namespace clt
{
	/**
  * @brief Class managing input actions and their states.
  */
	class CLUTTER_API Input
	{
	public:
		struct AxisMapping 
		{
			EKey positiveKey;
			EKey negativeKey;
		};

		struct MouseAxisMapping
		{
			EMouseButton positiveKey;
			EMouseButton negativeKey;
		};

		struct VectMapping 
		{
			EKey XpositiveKey;
			EKey XNegativeKey;

			EKey YpositiveKey;
			EKey YNegativeKey;
		};
		/**
	  * @brief Struct representing an action mapped to a key.
	  */
		struct Action {
			std::string name;  /**< Name of the action */
			EInputState state;  /**< State of the input */
			std::vector<std::function<void()>> callbacks;  /**< List of callbacks to be executed */
		};

	private:

		std::unordered_map<EKey, Action> mKeyActionMap;  /**< Map of key codes to actions */
		std::unordered_map<EKey, bool> mPreviousKeyStates;  /**< Map of previous key states */

		std::unordered_map<std::string, AxisMapping> mAxisMap;
		std::unordered_map<std::string, std::vector<std::function<void(float)>>> mAxisCallbacks;

		std::unordered_map<std::string, VectMapping> mVectMap;
		std::unordered_map<std::string, std::vector<std::function<void(Vector2)>>> mVectCallbacks;


		// Mouse
		std::unordered_map<EMouseButton, Action> mMouseActionMap;
		std::unordered_map<EMouseButton, bool> mPreviousMouseStates;
		std::unordered_map<std::string, MouseAxisMapping> mMouseAxisMap;
		std::vector<std::function<void(Vector2)>> mMouseDeltaCallback;
		std::vector<std::function<void(float)>>   mMouseScrollCallback;

		Vector2 mLastMousePosition;
		Vector2 mScrollDelta;

		bool mShowMouse = false;
		bool mLockMouse = true;

		// Controller
		std::unordered_map<EControllerButton, Action> mControllerActionMap;
		std::unordered_map<EControllerButton, bool> mPreviousControllerStates;
		std::unordered_map<std::string, EControllerAxis> mControllerAxisMap;

		float mControllerDeadzone = 0.2f;

		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
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

		void SetShowMouseCursor(bool show) { mShowMouse = show; };

		void LockMouseCursor(bool lock) { mLockMouse = lock; };
		/**
   * @brief Updates the state of the input manager.
   * @param pWindow Pointer to the GLFW window.
   */
		void Update(Window* pWindow);

		/**
   * @brief Maps a key to an action.
   * @param pKey Key code.
   * @param pActionName Name of the action.
   * @param pState State of the input.
   */
		void MapKeyToAction(EKey pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);
		void MapKeyToAction(EMouseButton pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);
		void MapKeyToAction(EControllerButton pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);

		/**
   * @brief Registers a callback for an action.
   * @param pActionName Name of the action.
   * @param callback Function to be called when the action is triggered.
   */
		void RegisterActionCallback(const std::string& pActionName, std::function<void()> callback);

		void RegisterAxisCallback(const std::string& axisName, std::function<void(float)> callback);

		void RegisterMouseCallback(std::function<void(Vector2)> callback);
		void RegisterScrollCallback(std::function<void(float)> callback);

		void MapKeysToAxis(EKey positiveKey, EKey negativeKey, const std::string& axisName);
		void MapKeysToAxis(EMouseButton positiveKey, EMouseButton negativeKey, const std::string& axisName);
		void MapKeysToAxis(EControllerAxis axis, const std::string& axisName, float pDeadzone = -1.0f);

		bool RegisterVectCallback(const std::string& VectName, std::function<void(Vector2)> callback);
		void MapKeysToVect(EKey XPositiveKey, EKey XNegativeKey, EKey YPositiveKey, EKey YNegativeKey, const std::string& VectName);
	};
}