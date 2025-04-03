#include "pch.h"
#include "TextElement.h"

using namespace clt;



TextElement::TextElement(std::string text, std::string font, Color color, float textSize, Vector2 position, int ZOrder)
	: WidgetElement(textSize, position, ZOrder), mText(text), mFont(nullptr), mColor(color)
{
	mFont = Assets::Get().GetFont(font);
}

TextElement::TextElement(std::string text, Font* font, Color color, float textSize, Vector2 position, int ZOrder) : WidgetElement(textSize, position, ZOrder), mText(text), mFont(font), mColor(color)
{
}

void TextElement::Draw(RendererGL* renderer)
{
}
