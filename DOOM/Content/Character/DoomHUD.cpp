#include "DoomHUD.h"


DoomHUD::DoomHUD() : HUDComponent(), mLifeState(100), mCanShoot(0.0f)
{
	CreateWidget<clt::UIPanel>("PlayerScreen");

	clt::Assets::Get().LoadFont("Content/Resources/Font/upheavtt.ttf", "hudfont");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/mainHUD.png", "hudFrame", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("mainFrame", "hudFrame", 8, Vector2{ 0, -600 }, 50);
	GetCurrentWidget()->CreateElement<clt::TextElement>("healthText", std::to_string(mLifeState) + "%", "hudfont", Color::red, 1.15f, Vector2{ -300, -280 }, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("armorText", "129%", "hudfont", Color::red, 1.15f, Vector2{180, -280}, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("ammoText", "55", "hudfont", Color::red, 1.15f, Vector2{ -500, -280 }, 100);

	std::vector<clt::Texture*> weapon = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 5, "_playerShoot.png", "pistolShoot", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::AnimatorElement>("playerWeapon", "pistolShoot", weapon, false, 10, 4, Vector2{0, -300});
}

void DoomHUD::Start()
{

}

void DoomHUD::Update()
{
	HUDComponent::Update();

	if (mCanShoot > 0.0f)
	{
		mCanShoot -= clt::Timer::deltaTime;
	}
}

void DoomHUD::TriggerShoot()
{

	if (mCanShoot <= 0.0f)
	{
		mCanShoot = 0.5f;
		GetCurrentWidget()->GetElement<clt::AnimatorElement>("playerWeapon")->PlayAnim("pistolShoot");

		raycastHit hitResult;
		LineTrace(GetWorldLocation(), GetWorldTransform().Forward(), 200, hitResult, true);
	}
}
