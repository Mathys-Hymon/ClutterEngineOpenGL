#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD() : HUDComponent()
{
	CreateWidget<clt::UIPanel>("mainMenu");
	CreateWidget<clt::UIPanel>("options");

	clt::Input::Get().SetShowMouseCursor(true);

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/doomLogo.png", "doomLogo");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/menuBackground.png", "menuBackground");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/newGame.png", "newGame", TextureFilter::NEAREST,false);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/newGameHovered.png", "newGameHovered", TextureFilter::NEAREST, false);

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/Options.png", "option", TextureFilter::NEAREST, false);
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/OptionsHovered.png", "optionHovered", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("logo", "doomLogo", 1.7, Vector2{ 0,400 });
	GetCurrentWidget()->CreateElement<clt::SpriteElement>("background", "menuBackground", 1.2f, Vector2::Zero, -100);
	

	GetCurrentWidget()->CreateElement<clt::ButtonElement>("playButton", "play")->Subscribe(clt::ButtonState::Pressed, [this]()
		{
			GetOwner()->GetLevel()->OpenLevel("Level");
		});

	GetCurrentWidget()->GetElement<clt::ButtonElement>("playButton")->SetPosition({ 0, -100 });
	GetCurrentWidget()->GetElement<clt::ButtonElement>("playButton")->SetSize(5);

	GetCurrentWidget()->GetElement<clt::ButtonElement>("playButton")->SetStateTexture(clt::ButtonState::None, "newGame");
	GetCurrentWidget()->GetElement<clt::ButtonElement>("playButton")->SetStateTexture(clt::ButtonState::Hovered, "newGameHovered");
	GetCurrentWidget()->GetElement<clt::ButtonElement>("playButton")->SetStateTexture(clt::ButtonState::Pressed, "newGameHovered");


	GetCurrentWidget()->CreateElement<clt::ButtonElement>("optionButton", "options")->SetPosition({0, -250});

	GetCurrentWidget()->GetElement<clt::ButtonElement>("optionButton")->SetSize(5);

	GetCurrentWidget()->GetElement<clt::ButtonElement>("optionButton")->SetStateTexture(clt::ButtonState::None, "option");
	GetCurrentWidget()->GetElement<clt::ButtonElement>("optionButton")->SetStateTexture(clt::ButtonState::Hovered, "optionHovered");
	GetCurrentWidget()->GetElement<clt::ButtonElement>("optionButton")->SetStateTexture(clt::ButtonState::Pressed, "optionHovered");

	//GetCurrentWidget()->CreateElement<clt::ButtonElement>("quitButton", "menuBackground", 1.2f, Vector2::Zero, -100);
}

void MainMenuHUD::Update()
{
	HUDComponent::Update();

	GetCurrentWidget()->GetElement<clt::SpriteElement>("logo")->SetPosition({ 0.0f, 400 + Maths::Sin(clt::Timer::GetTimeSinceLoad()) * 20 });
}
