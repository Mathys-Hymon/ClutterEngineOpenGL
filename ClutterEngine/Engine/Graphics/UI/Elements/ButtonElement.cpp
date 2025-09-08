#include "pch.h"
#include "ButtonElement.h"
#include "Input/Inputs.h"

using namespace clt;

ButtonElement::ButtonElement(std::string text, std::unordered_map<ButtonState, const std::string&> textures) :
	 SpriteElement(), mState(ButtonState::None)
{
	SetTextures(textures);
	SetTexture(mTextures[mState]);
}

ButtonElement::ButtonElement(std::string text, std::unordered_map<ButtonState, std::weak_ptr<Texture>> textures) :
	 SpriteElement(), mState(ButtonState::None)
{
	SetTextures(textures);
	SetTexture(mTextures[mState]);
}

void ButtonElement::Update()
{
	if (mState == ButtonState::Disabled)
		return;

	if (IsMouseOver(Inputs::Get().GetMousePosition()))
	{
		bool isPressed = Inputs::Get().IsButtonPressed(EMouseButton::Left);

		if (isPressed)
		{
			SetState(ButtonState::Pressed);
		}
		else
		{
			SetState(ButtonState::Hovered);
		}
	}
	else
	{
		SetState(ButtonState::None);
	}
}

void ButtonElement::Draw(RendererGL* renderer)
{
	SetTexture(mTextures[mState]);

	renderer->mSpriteShader.SetVec3f("tintColor", mTints[mState].rbg());

	SpriteElement::Draw(renderer);

	renderer->mSpriteShader.SetVec3f("tintColor", Vector3{ 1, 1, 1 });
}

void ButtonElement::SetState(ButtonState state)
{
	if (mState != state && mState != ButtonState::Disabled)
	{
		mState = state;
		SetTexture(mTextures[mState]);

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

bool ButtonElement::IsMouseOver(Vector2 mouse)
{
	Vector2 buttonPos = { GetPosition().x, -GetPosition().y * 0.5f};
	Vector2 buttonSize = GetSize();

	Vector2 windowSize = Window::Get().GetDimensions();

	Vector2 mousePos = mouse - (windowSize * 0.5f);

	return
		(mousePos.x >= buttonPos.x - buttonSize.x * 0.25f &&
			mousePos.x <= buttonPos.x + buttonSize.x * 0.25f &&
			mousePos.y >= buttonPos.y + buttonSize.y * 0.25f &&
			mousePos.y <= buttonPos.y - buttonSize.y * 0.25f);
}

void ButtonElement::SetTextures(std::unordered_map<ButtonState, const std::string&> textureNames)
{
	std::unordered_map<ButtonState, std::weak_ptr <Texture>> textures;

	std::weak_ptr<Texture> defaultTexture;

	for (const auto& [state, path] : textureNames)
	{
		auto tex = Assets::Get().GetTexture(path);
		textures[state] = tex;
		if (!defaultTexture.lock())
			defaultTexture = tex;
	}

	SetTextures(textures);
}

void ButtonElement::SetTextures(std::unordered_map<ButtonState, std::weak_ptr<Texture>> textures)
{
	mTextures = textures;

	std::weak_ptr<Texture> defaultTexture;
	if (!mTextures.empty()) defaultTexture = mTextures.begin()->second;
	else defaultTexture = Assets::Get().GetTexture("buttonBg");

	for (int i = 0; i <= static_cast<int>(ButtonState::Disabled); ++i)
	{
		ButtonState state = static_cast<ButtonState>(i);
		if (mTextures.find(state) == mTextures.end() && defaultTexture.lock())
		{
			mTextures[state] = defaultTexture;
		}
	}
}

void ButtonElement::SetStateTexture(ButtonState state, const std::string& texture, Color tint)
{
	mTextures[state] = Assets::Get().GetTexture(texture);
	mTints[state] = tint;
}

void ButtonElement::SetStateTexture(ButtonState state, std::weak_ptr<Texture> texture, Color tint)
{
	mTextures[state] = texture;
	mTints[state] = tint;
}

void ButtonElement::SetEnable(bool enable)
{
	mState = ButtonState::Disabled;
}

void ButtonElement::Subscribe(ButtonState state, Callback callback)
{
	mCallbacks[state].emplace_back(std::move(callback));
}
