#pragma once
#include "Graphics/UI/Elements/TextElement.h"
#include "Graphics/UI/Elements/SpriteElement.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace clt
{
	enum class CLUTTER_API ButtonState
	{
		None,
		Hovered,
		Pressed,
		Released,
		Disabled,
	};

	class CLUTTER_API ButtonElement : public SpriteElement
	{
		using Callback = std::function<void()>;

		ButtonState mState;
		std::unordered_map<ButtonState, std::vector<Callback>> mCallbacks;
		std::unordered_map<ButtonState, Texture*> mTextures;
		std::unordered_map<ButtonState, Color> mTints
		{
			{ButtonState::None, Color::White},
			{ButtonState::Hovered, Color::Light_grey},
			{ButtonState::Pressed, Color::Dark_grey},
			{ButtonState::Released, Color::White},
			{ButtonState::Disabled, Color::Grey},
		};

		void SetState(ButtonState state);
		bool IsMouseOver(Vector2 mousePos);

	public:
		ButtonElement(std::string text, std::unordered_map<ButtonState, const std::string&> texturesName = {});
		ButtonElement(std::string text, std::unordered_map<ButtonState, Texture*> textures);
		~ButtonElement() = default;

		virtual void Update() override;
		virtual void Draw(RendererGL* renderer) override;

		void SetTextures(std::unordered_map<ButtonState, const std::string&> textures);
		void SetTextures(std::unordered_map<ButtonState, Texture*> textures);
		void SetStateTexture(ButtonState state, const std::string& texture, Color tint = Color::White);
		void SetStateTexture(ButtonState state, Texture* texture, Color tint = Color::White);

		void SetEnable(bool enable = true);

		void Subscribe(ButtonState state, Callback callback);
	};
}