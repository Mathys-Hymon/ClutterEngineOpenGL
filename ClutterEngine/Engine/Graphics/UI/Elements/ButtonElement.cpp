#include "pch.h"
#include "ButtonElement.h"

using namespace clt;


ButtonElement::ButtonElement(std::string text, std::string texture) :
	SpriteElement(texture), TextElement(text)
{
}

ButtonElement::~ButtonElement()
{
}

void ButtonElement::Dispatch(ButtonState state)
{
	for (auto& callback : mCallbacks[state])
	{
		if (callback) callback();
	}
}

void ButtonElement::Update()
{
}

void ButtonElement::Draw(RendererGL* renderer)
{
	SpriteElement::Draw(renderer);
	TextElement::Draw(renderer);
}

void ButtonElement::Subscribe(ButtonState state, Callback callback)
{
	mCallbacks[state].push_back(callback);
}
