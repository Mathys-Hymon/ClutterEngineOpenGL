#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD() : HUDComponent()
{
	CreateWidget<clt::UIPanel>("mainMenu");
	CreateWidget<clt::UIPanel>("options");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/doomLogo.png", "doomLogo");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/menuBackground.png", "menuBackground");

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("logo", "doomLogo", 1.7, Vector2{ 0,400 });
	GetCurrentWidget()->CreateElement<clt::SpriteElement>("background", "menuBackground", 1.2f, Vector2::Zero, -100);
	

	//GetCurrentWidget()->CreateElement<clt::ButtonElement>("playButton", "menuBackground", 1.2f, Vector2::Zero, -100);

	//GetCurrentWidget()->CreateElement<clt::ButtonElement>("options", "menuBackground", 1.2f, Vector2::Zero, -100);

	//GetCurrentWidget()->CreateElement<clt::ButtonElement>("quitButton", "menuBackground", 1.2f, Vector2::Zero, -100);
}