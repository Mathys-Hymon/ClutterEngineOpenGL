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
		Hovered,
		Pressed,
		Released,
		Clicked
	};

	class CLUTTER_API ButtonElement : public TextElement, public SpriteElement
	{
		using Callback = std::function<void()>;

		ButtonState mState;
		std::unordered_map<ButtonState, std::vector<Callback>> mCallbacks;

		void Dispatch(ButtonState state);

	public:
		ButtonElement();
		~ButtonElement();

		virtual void Update() override;
		virtual void Draw(RendererGL* renderer) override;

		void Subscribe(ButtonState state, Callback callback);
	};
}