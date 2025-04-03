#pragma once
#include <Graphics/UI/WidgetElement.h>
#include <Graphics/RendererGL.h>

namespace clt
{
	class CLUTTER_API TextElement : public WidgetElement
	{
	public:
		std::string mText;
		Color mColor;
		Font* mFont;

		TextElement(std::string text = "Hello World !", std::string font = "ClutterFont.ttf", Color color = Color::white, float textSize = 48, Vector2 position = { 0, 0 }, int ZOrder = 0);

		TextElement(std::string text, Font* font, Color color = Color::white, float textSize = 48, Vector2 position = { 0, 0 }, int ZOrder = 0);

		virtual ~TextElement() = default;

		virtual void Draw(RendererGL* renderer) override;
	};
}