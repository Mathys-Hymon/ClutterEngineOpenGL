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
		/**
   * @brief Struct representing a mapping between two keys for an axis.
   */
		struct AxisMapping 
		{
			EKey positiveKey;   /**< Key representing the positive direction of the axis */
			EKey negativeKey;   /**< Key representing the negative direction of the axis */
		};

		/**
   * @brief Struct representing a mapping between two mouse buttons for an axis.
   */
		struct MouseAxisMapping
		{
			EMouseButton positiveKey;   /**< Mouse button for positive direction */
			EMouseButton negativeKey;   /**< Mouse button for negative direction */
		};

		/**
   * @brief Struct representing a mapping for a 2D vector using four keys.
   */
		struct VectMapping 
		{
			EKey XpositiveKey;   /**< Key for positive X direction */
			EKey XNegativeKey;   /**< Key for negative X direction */
			EKey YpositiveKey;   /**< Key for positive Y direction */
			EKey YNegativeKey;   /**< Key for negative Y direction */
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

		std::unordered_map<EKey, std::vector<Action>> mKeyActionMap;  /**< Map of key codes to actions */
		std::unordered_map<EKey, bool> mPreviousKeyStates;  /**< Map of previous key states */

		std::unordered_map<std::string, AxisMapping> mAxisMap;  /**< Map of axis names to key mappings */
		std::unordered_map<std::string, std::vector<std::function<void(float)>>> mAxisCallbacks;  /**< Map of axis names to callbacks */

		std::unordered_map<std::string, VectMapping> mVectMap;  /**< Map of vector names to key mappings */
		std::unordered_map<std::string, std::vector<std::function<void(Vector2)>>> mVectCallbacks;  /**< Map of vector names to callbacks */

		// Mouse
		std::unordered_map<EMouseButton, std::vector<Action>> mMouseActionMap;  /**< Map of mouse buttons to actions */
		std::unordered_map<EMouseButton, bool> mPreviousMouseStates;  /**< Map of previous mouse button states */
		std::unordered_map<std::string, MouseAxisMapping> mMouseAxisMap;  /**< Map of axis names to mouse button mappings */
		std::vector<std::function<void(Vector2)>> mMouseDeltaCallback;  /**< List of mouse delta callbacks */
		std::vector<std::function<void(float)>>   mMouseScrollCallback; /**< List of mouse scroll callbacks */

		Vector2 mLastMousePosition;  /**< Last recorded mouse position */
		Vector2 mScrollDelta;        /**< Mouse scroll delta */

		bool mShowMouse = false;     /**< Whether to show the mouse cursor */
		bool mLockMouse = true;      /**< Whether to lock the mouse cursor */

		// Controller
		std::unordered_map<EControllerButton, std::vector<Action>> mControllerActionMap;  /**< Map of controller buttons to actions */
		std::unordered_map<EControllerButton, bool> mPreviousControllerStates;            /**< Map of previous controller button states */
		std::unordered_map<std::string, EControllerAxis> mControllerAxisMap;              /**< Map of axis names to controller axes */

		float mControllerDeadzone = 0.2f; /**< Deadzone for controller axis input */

		/**
   * @brief GLFW scroll callback.
   * @param window Pointer to the GLFW window.
   * @param xoffset Scroll offset in the X direction.
   * @param yoffset Scroll offset in the Y direction.
   */
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

		/**
   * @brief Sets whether to show the mouse cursor.
   * @param show True to show the cursor, false to hide.
   */
		void SetShowMouseCursor(bool show) { mShowMouse = show; };

		/**
   * @brief Locks or unlocks the mouse cursor.
   * @param lock True to lock the cursor, false to unlock.
   */
		void LockMouseCursor(bool lock) { mLockMouse = lock; };

		/**
   * @brief Gets the current mouse position.
   * @return The last recorded mouse position.
   */
		Vector2 GetMousePosition() const { return mLastMousePosition; };

		/**
   * @brief Checks if a key is pressed.
   * @param pKey The key to check.
   * @return True if the key is pressed, false otherwise.
   */
		bool IsButtonPressed(EKey pKey) const;

		/**
   * @brief Checks if a mouse button is pressed.
   * @param pButton The mouse button to check.
   * @return True if the button is pressed, false otherwise.
   */
		bool IsButtonPressed(EMouseButton pButton) const;

		/**
   * @brief Updates the state of the input manager.
   */
		void Update();

		/**
   * @brief Maps a key to an action.
   * @param pKey Key code.
   * @param pActionName Name of the action.
   * @param pState State of the input.
   */
		void MapKeyToAction(EKey pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);

		/**
   * @brief Maps a mouse button to an action.
   * @param pKey Mouse button code.
   * @param pActionName Name of the action.
   * @param pState State of the input.
   */
		void MapKeyToAction(EMouseButton pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);

		/**
   * @brief Maps a controller button to an action.
   * @param pKey Controller button code.
   * @param pActionName Name of the action.
   * @param pState State of the input.
   */
		void MapKeyToAction(EControllerButton pKey, const std::string& pActionName, EInputState pState = EInputState::Pressed);

		/**
   * @brief Registers a callback for an action.
   * @param pActionName Name of the action.
   * @param callback Function to be called when the action is triggered.
   */
		void RegisterActionCallback(const std::string& pActionName, std::function<void()> callback);

		/**
   * @brief Registers a callback for an axis.
   * @param axisName Name of the axis.
   * @param callback Function to be called with the axis value.
   */
		void RegisterAxisCallback(const std::string& axisName, std::function<void(float)> callback);

		/**
   * @brief Registers a callback for mouse movement.
   * @param callback Function to be called with the mouse delta.
   */
		void RegisterMouseCallback(std::function<void(Vector2)> callback);

		/**
   * @brief Registers a callback for mouse scroll.
   * @param callback Function to be called with the scroll value.
   */
		void RegisterScrollCallback(std::function<void(float)> callback);

		/**
   * @brief Maps two keys to an axis.
   * @param positiveKey Key for positive direction.
   * @param negativeKey Key for negative direction.
   * @param axisName Name of the axis.
   */
		void MapKeysToAxis(EKey positiveKey, EKey negativeKey, const std::string& axisName);

		/**
   * @brief Maps two mouse buttons to an axis.
   * @param positiveKey Mouse button for positive direction.
   * @param negativeKey Mouse button for negative direction.
   * @param axisName Name of the axis.
   */
		void MapKeysToAxis(EMouseButton positiveKey, EMouseButton negativeKey, const std::string& axisName);

		/**
   * @brief Maps a controller axis to an axis name.
   * @param axis Controller axis.
   * @param axisName Name of the axis.
   * @param pDeadzone Deadzone for the axis (optional).
   */
		void MapKeysToAxis(EControllerAxis axis, const std::string& axisName, float pDeadzone = -1.0f);

		/**
   * @brief Registers a callback for a vector input.
   * @param VectName Name of the vector input.
   * @param callback Function to be called with the vector value.
   * @return True if registration was successful, false otherwise.
   */
		bool RegisterVectCallback(const std::string& VectName, std::function<void(Vector2)> callback);

		/**
   * @brief Maps four keys to a 2D vector input.
   * @param XPositiveKey Key for positive X direction.
   * @param XNegativeKey Key for negative X direction.
   * @param YPositiveKey Key for positive Y direction.
   * @param YNegativeKey Key for negative Y direction.
   * @param VectName Name of the vector input.
   */
		void MapKeysToVect(EKey XPositiveKey, EKey XNegativeKey, EKey YPositiveKey, EKey YNegativeKey, const std::string& VectName);
	};
}
