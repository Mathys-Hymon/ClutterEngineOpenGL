#include "pch.h"
#include <Input/Input.h>

using namespace clt;

void Input::MapKeyToAction(EKey pKey, const std::string& pActionName, EInputState pState)
{
	mKeyActionMap[pKey] = {pActionName, pState, {}};
}

void Input::RegisterActionCallback(const std::string& pActionName, std::function<void()> callback)
{
	for (auto& [key, action] : mKeyActionMap)
	{
		if (action.name == pActionName)
		{
			action.callbacks.push_back(callback);
			break;
		}
	}
}

void Input::RegisterAxisCallback(const std::string& axisName, std::function<void(float)> callback)
{
	mAxisCallbacks[axisName].push_back(callback);
}

void Input::MapKeysToAxis(EKey positiveKey, EKey negativeKey, const std::string& axisName)
{
	mAxisMap[axisName] = { positiveKey, negativeKey };
}

void Input::Update(GLFWwindow* pWindow)
{
			// INPUT MAPPING

	for (auto& [key, action] : mKeyActionMap)
	{
		bool isKeyPressed = glfwGetKey(pWindow, static_cast<int>(key)) == GLFW_PRESS;
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

		if (currentState == action.state)
		{
			for (std::function<void()> callback : action.callbacks)
			{
				callback();
			}
		}
		mPreviousKeyStates[key] = isKeyPressed;


			// AXIS MAPPING

		for (const auto& [axisName, axisMapping] : mAxisMap)
		{
			float axisValue = 0.0f;

			if (glfwGetKey(pWindow, static_cast<int>(axisMapping.positiveKey)) == GLFW_PRESS)
				axisValue += 1.0f;
			if (glfwGetKey(pWindow, static_cast<int>(axisMapping.negativeKey)) == GLFW_PRESS)
				axisValue -= 1.0f;

			if (mAxisCallbacks.find(axisName) != mAxisCallbacks.end())
			{
				for (const auto& callback : mAxisCallbacks[axisName])
				{
					callback(axisValue);
				}
			}
		}
	}
}
