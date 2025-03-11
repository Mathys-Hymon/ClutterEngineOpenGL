#pragma once
#include <Graphics/UI/WidgetElement.h>

namespace clt
{
	class CLUTTER_API SpriteElement : public WidgetElement
	{
	public:

		SpriteElement(const std::string spriteName, Vector2 size = { 25,25 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(spriteName, size, position, ZOrder) {};

		SpriteElement(Texture* sprite, Vector2 size = { 25,25 }, Vector2 position = { 0, 0 }, int ZOrder = 0) :
			WidgetElement(sprite, size, position, ZOrder) {};

		virtual void Update() override {};
	};
}