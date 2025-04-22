#pragma once
#include "Graphics/UI/Elements/TextElement.h"
#include "Graphics/UI/Elements/SpriteElement.h"

namespace clt
{
	enum class CLUTTER_API ButtonState
	{
		none,
		hovered,
		pressed,
	};

	class CLUTTER_API ButtonElement : public TextElement, public SpriteElement
	{
		ButtonState mState;

	public:
		ButtonElement();
		~ButtonElement();

	};
}