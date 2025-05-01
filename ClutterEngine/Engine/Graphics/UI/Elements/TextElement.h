#pragma once
#include <Graphics/UI/WidgetElement.h>
#include <Graphics/RendererGL.h>


enum class CLUTTER_API TextAlignment
{
	Left,
	Center,
	Right,
};

namespace clt
{
	class CLUTTER_API TextElement : public virtual WidgetElement
	{
		std::string mText;
		Color mColor;
		Font* mFont;

		float mWidth;

		TextAlignment mAlignment;

		GLuint VAO, VBO;

		void CalculateWidth();

	public:

		TextElement(std::string text = "Hello World !", std::string font = "BebasNeue", Color color = Color::White, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		TextElement(std::string text, Color color, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		TextElement(std::string text, Font* font, Color color = Color::White, float textSize = 1, Vector2 position = { 0, 0 }, int ZOrder = 0);

		~TextElement();

		void SetText(std::string text);

		void SetText(int text);

		void SetSize(float size);

		void SetColor(Color color);

		void SetAlignment(TextAlignment alignment);

		float GetTextWidth() const { return mWidth; };

		virtual void Draw(RendererGL* renderer) override;
	};
}