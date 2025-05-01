#include "pch.h"
#include "ButtonElement.h"
#include "Input/Input.h"

using namespace clt;

ButtonElement::ButtonElement(std::string text, std::unordered_map<ButtonState, const std::string&> textures) :
	TextElement(text), SpriteElement(), mState(ButtonState::None)
{
	SetTextures(textures);
}

ButtonElement::ButtonElement(std::string text, std::unordered_map<ButtonState, Texture*> textures) :
	TextElement(text), SpriteElement(), mState(ButtonState::None)
{
	SetTextures(textures);
}

void ButtonElement::Update()
{
	SpriteElement::GetSize();
	if (mState == ButtonState::Disabled)
		return;
}

void ButtonElement::Draw(RendererGL* renderer)
{
	SetTexture(mTextures[mState]);

	if (mState == ButtonState::Disabled)
	{
		renderer->mSpriteShader.SetVec3f("tintColor", Vector3{ 0.5f, 0.5f, 0.5f });
	}
	else
	{
		renderer->mSpriteShader.SetVec3f("tintColor", Vector3{ 0.5f, 0.5f, 0.5f });
	}

	SpriteElement::Draw(renderer);
	TextElement::Draw(renderer);
}

void ButtonElement::SetState(ButtonState state)
{
	if (mState != state && mState != ButtonState::Disabled)
	{
		mState = state;
		auto it = mCallbacks.find(mState);
		if (it != mCallbacks.end())
		{
			for (auto& callback : it->second)
			{
				callback();
			}
		}
	}
}

void ButtonElement::SetTextures(std::unordered_map<ButtonState, const std::string&> textureNames)
{
	for (const auto& [state, path] : textureNames)
	{
		mTextures[state] = Assets::Get().GetTexture(path);
	}
}

void ButtonElement::SetTextures(std::unordered_map<ButtonState, Texture*> textures)
{
	mTextures = std::move(textures);
}

void ButtonElement::SetEnable(bool enable)
{
	mState = ButtonState::Disabled;
}

void ButtonElement::Subscribe(ButtonState state, Callback callback)
{
	mCallbacks[state].emplace_back(std::move(callback));
}
