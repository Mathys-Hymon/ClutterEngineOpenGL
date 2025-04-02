#pragma once
#include <Graphics/UI/WidgetElement.h>

namespace clt
{
	class CLUTTER_API TextElement : public WidgetElement
	{
	public:
		std::string mText;
		Color mColor;

		TextElement(std::string text = "Hello World !", std::string font = "ClutterFont.ttf", Color color = Color::white, float textSize = 48);

		TextElement(std::string text, Font* font, Color color = Color::white, float textSize = 48);

		virtual ~TextElement();

	};
}