#include "DoomHUD.h"


DoomHUD::DoomHUD() : HUDComponent(), mLifeState(3), mCanShoot(0.0f)
{
	CreateWidget<clt::UIPanel>("PlayerScreen");

	clt::Assets::Get().LoadFont("Content/Resources/Font/upheavtt.ttf", "hudfont");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/mainHUD.png", "hudFrame", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("mainFrame", "hudFrame", 8, Vector2{ 0, -600 }, 50);
	GetCurrentWidget()->CreateElement<clt::TextElement>("healthText", std::to_string(mLifeState) + "%", "hudfont", Color::Red, 1.15f, Vector2{ -300, -280 }, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("armorText", "129%", "hudfont", Color::Red, 1.15f, Vector2{180, -280}, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("ammoText", "55", "hudfont", Color::Red, 1.15f, Vector2{ -500, -280 }, 100);

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

bool DoomHUD::TriggerShoot(int ammo)
{

	if (mCanShoot <= 0.0f)
	{
		mCanShoot = 0.5f;
		GetCurrentWidget()->GetElement<clt::AnimatorElement>("playerWeapon")->PlayAnim("pistolShoot");
		GetCurrentWidget()->GetElement<clt::TextElement>("ammoText")->SetText(ammo);

		raycastHit hitResult;

		LineTrace(GetWorldLocation(), GetWorldTransform().Forward(), 150, hitResult);
		return true;
	}

	else
	{
		return false;
	}
}

void DoomHUD::UpdateLifeState(int pLifeState)
{
	mLifeState = pLifeState;
}
