#pragma once
#include "Graphics/UI/Elements/TextElement.h"
#include "Graphics/UI/Elements/SpriteElement.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace clt
{
	/**
  * @brief Represents the possible states of a button element.
  */
	enum class CLUTTER_API ButtonState
	{
		None,      /**< Default state, no interaction. */
		Hovered,   /**< Mouse is hovering over the button. */
		Pressed,   /**< Button is being pressed. */
		Released,  /**< Button was just released. */
		Disabled,  /**< Button is disabled and cannot be interacted with. */
	};

	/**
  * @brief UI element representing a button with different states, textures, and callbacks.
  */
	class CLUTTER_API ButtonElement : public SpriteElement
	{
		using Callback = std::function<void()>;

		ButtonState mState; ///< Current state of the button.
		std::unordered_map<ButtonState, std::vector<Callback>> mCallbacks; ///< Callbacks for each button state.
		std::unordered_map<ButtonState, Texture*> mTextures; ///< Textures for each button state.
		std::unordered_map<ButtonState, Color> mTints
		{
			{ButtonState::None, Color::White},
			{ButtonState::Hovered, Color::Light_grey},
			{ButtonState::Pressed, Color::Dark_grey},
			{ButtonState::Released, Color::White},
			{ButtonState::Disabled, Color::Grey},
		}; ///< Color tints for each button state.

		/**
   * @brief Sets the current state of the button.
   * @param state The new state to set.
   */
		void SetState(ButtonState state);

		/**
   * @brief Checks if the mouse is over the button.
   * @param mousePos The position of the mouse.
   * @return True if the mouse is over the button, false otherwise.
   */
		bool IsMouseOver(Vector2 mousePos);

	public:
		/**
   * @brief Constructs a ButtonElement with text and optional texture names for each state.
   * @param text The text to display on the button.
   * @param texturesName Map of button states to texture names.
   */
		ButtonElement(std::string text, std::unordered_map<ButtonState, const std::string&> texturesName = {});

		/**
   * @brief Constructs a ButtonElement with text and textures for each state.
   * @param text The text to display on the button.
   * @param textures Map of button states to textures.
   */
		ButtonElement(std::string text, std::unordered_map<ButtonState, Texture*> textures);

		/**
   * @brief Destructor.
   */
		~ButtonElement() = default;

		/**
   * @brief Updates the button state and handles input.
   */
		virtual void Update() override;

		/**
   * @brief Draws the button using the specified renderer.
   * @param renderer The renderer to use.
   */
		virtual void Draw(RendererGL* renderer) override;

		/**
   * @brief Sets textures for each button state using texture names.
   * @param textures Map of button states to texture names.
   */
		void SetTextures(std::unordered_map<ButtonState, const std::string&> textures);

		/**
   * @brief Sets textures for each button state.
   * @param textures Map of button states to textures.
   */
		void SetTextures(std::unordered_map<ButtonState, Texture*> textures);

		/**
   * @brief Sets the texture and tint for a specific button state using a texture name.
   * @param state The button state.
   * @param texture The texture name.
   * @param tint The color tint to apply.
   */
		void SetStateTexture(ButtonState state, const std::string& texture, Color tint = Color::White);

		/**
   * @brief Sets the texture and tint for a specific button state.
   * @param state The button state.
   * @param texture The texture pointer.
   * @param tint The color tint to apply.
   */
		void SetStateTexture(ButtonState state, Texture* texture, Color tint = Color::White);

		/**
   * @brief Enables or disables the button.
   * @param enable True to enable, false to disable.
   */
		void SetEnable(bool enable = true);

		/**
   * @brief Subscribes a callback to a specific button state event.
   * @param state The button state to subscribe to.
   * @param callback The callback function to invoke.
   */
		void Subscribe(ButtonState state, Callback callback);
	};
}
