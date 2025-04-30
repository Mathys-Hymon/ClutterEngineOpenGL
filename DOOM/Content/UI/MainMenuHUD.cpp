#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD() : HUDComponent()
{
	CreateWidget<clt::UIPanel>("mainMenu");
	CreateWidget<clt::UIPanel>("options");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/doomLogo.png", "doomLogo", TextureFilter::NEAREST, false);

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/menuBackground.png", "menuBackground", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("logo", "doomLogo", 1.7, Vector2{ 0,400 });
	GetCurrentWidget()->CreateElement<clt::SpriteElement>("logo", "menuBackground", 2.6f, Vector2::Zero, -100);
}
