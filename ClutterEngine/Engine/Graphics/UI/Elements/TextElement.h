#pragma once
#include <Graphics/UI/WidgetElement.h>
#include <Graphics/RendererGL.h>

/**
 * @brief Specifies the alignment of text within a TextElement.
 */
enum class CLUTTER_API TextAlignment
{
	Left,   ///< Align text to the left.
	Center, ///< Center the text.
	Right,  ///< Align text to the right.
};

namespace clt
{
	/**
  * @brief UI element for rendering text.
  * 
  * TextElement allows displaying and customizing text in the UI, including font, color, size, and alignment.
  */
	class CLUTTER_API TextElement : public WidgetElement
	{
		std::string mText;      ///< The text string to display.
		Color mColor;           ///< The color of the text.
		Font* mFont;            ///< Pointer to the font used for rendering.
		float mWidth;           ///< The calculated width of the text.
		TextAlignment mAlignment;///< The alignment of the text.
		GLuint VAO, VBO;        ///< OpenGL handles for rendering.

		/**
   * @brief Calculates the width of the current text string.
   */
		void CalculateWidth();

	public:

		/**
   * @brief Constructs a TextElement with specified text, font name, color, size, position, and Z order.
   * @param text The text to display.
   * @param font The font name to use.
   * @param color The color of the text.
   * @param textSize The size of the text.
   * @param position The position of the text element.
   * @param ZOrder The Z order for rendering.
   */
		TextElement(std::string text = "Hello World !", std::string font = "BebasNeue", Color color = Color::White, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		/**
   * @brief Constructs a TextElement with specified text, color, size, position, and Z order.
   * @param text The text to display.
   * @param color The color of the text.
   * @param textSize The size of the text.
   * @param position The position of the text element.
   * @param ZOrder The Z order for rendering.
   */
		TextElement(std::string text, Color color, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		/**
   * @brief Constructs a TextElement with specified text, font pointer, color, size, position, and Z order.
   * @param text The text to display.
   * @param font Pointer to the font to use.
   * @param color The color of the text.
   * @param textSize The size of the text.
   * @param position The position of the text element.
   * @param ZOrder The Z order for rendering.
   */
		TextElement(std::string text, Font* font, Color color = Color::White, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		/**
   * @brief Destructor for TextElement.
   */
		~TextElement();

		/**
   * @brief Sets the text string to display.
   * @param text The new text string.
   */
		void SetText(std::string text);

		/**
   * @brief Sets the text string to display using an integer value.
   * @param text The integer to convert and display as text.
   */
		void SetText(int text);

		/**
   * @brief Sets the size of the text.
   * @param size The new text size.
   */
		void SetSize(float size);

		/**
   * @brief Sets the color of the text.
   * @param color The new text color.
   */
		void SetColor(Color color);

		/**
   * @brief Sets the alignment of the text.
   * @param alignment The new text alignment.
   */
		void SetAlignment(TextAlignment alignment);

		/**
   * @brief Gets the width of the current text string.
   * @return The width of the text.
   */
		float GetTextWidth() const { return mWidth; };

		/**
   * @brief Draws the text element using the specified renderer.
   * @param renderer The renderer to use for drawing.
   */
		virtual void Draw(RendererGL* renderer) override;
	};
}
