#include "pch.h"
#include "Core/CEngine.h"
#include <Input/Input.h>

using namespace clt;

void Input::MapKeyToAction(EKey pKey, const std::string& pActionName, EInputState pState)
{
	mKeyActionMap[pKey].push_back({pActionName, pState, {}});
}

void Input::MapKeyToAction(EMouseButton pKey, const std::string& pActionName, EInputState pState)
{
	mMouseActionMap[pKey].push_back({ pActionName, pState, {} });
}

void Input::MapKeyToAction(EControllerButton pKey, const std::string& pActionName, EInputState pState)
{
	mControllerActionMap[pKey].push_back({ pActionName, pState, {} });
}

void Input::RegisterActionCallback(const std::string& pActionName, std::function<void()> callback)
{
	for (auto& [key, actions] : mKeyActionMap)
	{
		for (auto& action : actions)
		{
			if (action.name == pActionName)
			{
				action.callbacks.push_back(callback);
				break;
			}
		}
	}

	for (auto& [key, actions] : mMouseActionMap)
	{
		for (auto& action : actions)
		{
			if (action.name == pActionName)
			{
				action.callbacks.push_back(callback);
				break;
			}
		}
	}

	for (auto& [key, actions] : mControllerActionMap)
	{
		for (auto& action : actions)
		{
			if (action.name == pActionName)
			{
				action.callbacks.push_back(callback);
				break;
			}
		}
	}
}

void Input::RegisterAxisCallback(const std::string& axisName, std::function<void(float)> callback)
{
	mAxisCallbacks[axisName].push_back(callback);
}

void Input::RegisterMouseCallback(std::function<void(Vector2)> callback)
{
	mMouseDeltaCallback.push_back(callback);
}

void Input::RegisterScrollCallback(std::function<void(float)> callback)
{
	mMouseScrollCallback.push_back(callback);
}

void Input::MapKeysToAxis(EKey positiveKey, EKey negativeKey, const std::string& axisName)
{
	mAxisMap[axisName] = { positiveKey, negativeKey };
}

void Input::MapKeysToAxis(EMouseButton positiveKey, EMouseButton negativeKey, const std::string& axisName)
{
	mMouseAxisMap[axisName] = { positiveKey, negativeKey };
}

void Input::MapKeysToAxis(EControllerAxis axis, const std::string& axisName, float pDeadzone)
{
	mControllerAxisMap[axisName] = { axis };

	if(pDeadzone >= 0) mControllerDeadzone = pDeadzone;
}

bool Input::RegisterVectCallback(const std::string& VectName, std::function<void(Vector2)> callback)
{
	if (mVectMap.count(VectName))
	{
		mVectCallbacks[VectName].push_back(callback);
		return true;
	}
	return false;
}

void Input::MapKeysToVect(EKey XPositiveKey, EKey XNegativeKey, EKey YPositiveKey, EKey YNegativeKey, const std::string& VectName)
{
	mVectMap[VectName] = { XPositiveKey , XNegativeKey , YPositiveKey, YNegativeKey };
}

bool Input::IsButtonPressed(EKey pKey) const
{
	return glfwGetKey(CEngine::Get().GetWindow()->GetGLFWWindow(), static_cast<int>(pKey)) == GLFW_PRESS;
}

bool Input::IsButtonPressed(EMouseButton pButton) const
{
	return glfwGetMouseButton(CEngine::Get().GetWindow()->GetGLFWWindow(), static_cast<int>(pButton)) == GLFW_PRESS;
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::Get().mScrollDelta.x += static_cast<float>(xoffset);
	Input::Get().mScrollDelta.y += static_cast<float>(yoffset);
}

void Input::Update(Window* pWindow)
{
	GLFWwindow* pGLFWindow = pWindow->GetGLFWWindow();
	glfwSetScrollCallback(pGLFWindow, ScrollCallback);
		// INPUT MAPPING

	for (auto& [key, actions] : mKeyActionMap)
	{
		bool isKeyPressed = glfwGetKey(pGLFWindow, static_cast<int>(key)) == GLFW_PRESS;
		bool wasKeyPressed = mPreviousKeyStates[key];

		EInputState currentState = EInputState::Held;

		if (isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Pressed;
		} 
		else if (!isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Released;
		}

		for (auto& action : actions)
		{
			if (currentState == action.state)
			{
				for (std::function<void()> callback : action.callbacks)
				{
					callback();
				}
			}
		}
		mPreviousKeyStates[key] = isKeyPressed;
	}

	for (auto& [key, actions] : mControllerActionMap)
	{
		bool isKeyPressed = glfwGetKey(pGLFWindow, static_cast<int>(key)) == GLFW_PRESS;
		bool wasKeyPressed = mPreviousControllerStates[key];

		EInputState currentState = EInputState::Held;

		if (isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Pressed;
		}
		else if (!isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Released;
		}

		for (auto& action : actions)
		{
			if (currentState == action.state)
			{
				for (std::function<void()> callback : action.callbacks)
				{
					callback();
				}
			}
		}
		mPreviousControllerStates[key] = isKeyPressed;
	}

	for (auto& [key, actions] : mMouseActionMap)
	{
		int glfwBtn = static_cast<int>(key);
		bool isKeyPressed = glfwGetMouseButton(pGLFWindow, glfwBtn) == GLFW_PRESS;

		bool wasKeyPressed = mPreviousMouseStates[key];

		EInputState currentState = EInputState::Held;

		if (isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Pressed;
		}
		else if (!isKeyPressed && wasKeyPressed)
		{
			currentState = EInputState::Released;
		}
		else if (!isKeyPressed && !wasKeyPressed)
		{
			currentState = EInputState::Idle;
		}

		for (auto& action : actions)
		{
			if (currentState == action.state)
			{
				for (std::function<void()> callback : action.callbacks)
				{
					callback();
				}
			}
		}

		mPreviousMouseStates[key] = isKeyPressed;
	}

		// AXIS MAPPING

	for (const auto& [axisName, axisMapping] : mAxisMap)
	{
		float axisValue = 0.0f;

		if (glfwGetKey(pGLFWindow, static_cast<int>(axisMapping.positiveKey)) == GLFW_PRESS)
			axisValue += 1.0f;
		if (glfwGetKey(pGLFWindow, static_cast<int>(axisMapping.negativeKey)) == GLFW_PRESS)
			axisValue -= 1.0f;

		if (mAxisCallbacks.find(axisName) != mAxisCallbacks.end())
		{
			for (const auto& callback : mAxisCallbacks[axisName])
			{
				callback(axisValue);
			}
		}
	}

	for (const auto& [axisName, MouseAxisMapping] : mMouseAxisMap)
	{
		float axisValue = 0.0f;

		if (glfwGetKey(pGLFWindow, static_cast<int>(MouseAxisMapping.positiveKey)) == GLFW_PRESS)
			axisValue += 1.0f;
		if (glfwGetKey(pGLFWindow, static_cast<int>(MouseAxisMapping.negativeKey)) == GLFW_PRESS)
			axisValue -= 1.0f;

		if (mAxisCallbacks.find(axisName) != mAxisCallbacks.end())
		{
			for (const auto& callback : mAxisCallbacks[axisName])
			{
				callback(axisValue);
			}
		}
	}

	double mouseX, mouseY;
	glfwGetCursorPos(pGLFWindow, &mouseX, &mouseY);
	Vector2 currentMousePos(static_cast<float>(mouseX), static_cast<float>(mouseY));
	Vector2 mouseDelta = currentMousePos - mLastMousePosition;
	mLastMousePosition = currentMousePos;

	for (const auto& callback : mMouseDeltaCallback)
	{
		callback(mouseDelta);
	}

	for (const auto& [axisName, MouseAxisMapping] : mMouseAxisMap)
	{
		float axisValue = 0.0f;

		if (glfwGetKey(pGLFWindow, static_cast<int>(MouseAxisMapping.positiveKey)) == GLFW_PRESS)
			axisValue += 1.0f;
		if (glfwGetKey(pGLFWindow, static_cast<int>(MouseAxisMapping.negativeKey)) == GLFW_PRESS)
			axisValue -= 1.0f;

		if (mAxisCallbacks.find(axisName) != mAxisCallbacks.end())
		{
			for (const auto& callback : mAxisCallbacks[axisName])
			{
				callback(axisValue);
			}
		}
	}

		// VECTOR MAPPING

	for (const auto& [vectName, vectMapping] : mVectMap)
	{
		Vector2 vectValue = { 0.0f, 0.0f };

		bool isVectorPressed = false;

		if (glfwGetKey(pGLFWindow, static_cast<int>(vectMapping.XpositiveKey)) == GLFW_PRESS)
		{
			isVectorPressed = true;
			vectValue.x += 1.0f;
		}

		if (glfwGetKey(pGLFWindow, static_cast<int>(vectMapping.XNegativeKey)) == GLFW_PRESS)
		{
			isVectorPressed = true;
			vectValue.x -= 1.0f;
		}

		if (glfwGetKey(pGLFWindow, static_cast<int>(vectMapping.YpositiveKey)) == GLFW_PRESS)
		{
			isVectorPressed = true;
			vectValue.y += 1.0f;
		}

		if (glfwGetKey(pGLFWindow, static_cast<int>(vectMapping.YNegativeKey)) == GLFW_PRESS)
		{
			isVectorPressed = true;
			vectValue.y -= 1.0f;
		}

		if(vectValue.Length() > 0)	vectValue.Normalized();
		
		if (mVectCallbacks.find(vectName) != mVectCallbacks.end())
		{
			if (isVectorPressed || mPreviousKeyStates[vectMapping.XpositiveKey])
			{
				mPreviousKeyStates[vectMapping.XpositiveKey] = true;

				for (const auto& callback : mVectCallbacks[vectName])
				{
					callback(vectValue);
				}
				if (!isVectorPressed) mPreviousKeyStates[vectMapping.XpositiveKey] = false;
			}
		}
	}

	glfwSetInputMode(pGLFWindow, GLFW_CURSOR, mShowMouse ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	mScrollDelta = 0.0f;
}
