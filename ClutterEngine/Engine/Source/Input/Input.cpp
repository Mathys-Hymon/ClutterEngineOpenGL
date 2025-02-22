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

void Input::RegisterVectCallback(const std::string& VectName, std::function<void(Vector2)> callback)
{
	mVectCallbacks[VectName].push_back(callback);
}

void Input::MapKeysToVect(EKey XPositiveKey, EKey XNegativeKey, EKey YPositiveKey, EKey YNegativeKey, const std::string& VectName)
{
	mVectMap[VectName] = { XPositiveKey , XNegativeKey , YPositiveKey, YNegativeKey };
}

void Input::Update(Window* pWindow)
{
	GLFWwindow* pGLFWindow = pWindow->GetGLFWWindow();

			// INPUT MAPPING

	for (auto& [key, action] : mKeyActionMap)
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

		if (currentState == action.state)
		{
			for (std::function<void()> callback : action.callbacks)
			{
				callback();
			}
		}
		mPreviousKeyStates[key] = isKeyPressed;
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

		if(vectValue.Length() > 0)	vectValue.Normalize();
		
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
}
