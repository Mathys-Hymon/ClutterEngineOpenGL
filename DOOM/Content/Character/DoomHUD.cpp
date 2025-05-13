#include "DoomHUD.h"
#include <cstdlib> 
#include "Gameplay/Enemy/Zombie.h"


DoomHUD::DoomHUD() : HUDComponent(), mLifeState(3), mCanShoot(0.0f), mTauntDelay(1), mLife(100)
{

	clt::Input::Get().SetShowMouseCursor(false);

	CreateWidget<clt::UIPanel>("PlayerScreen");

	clt::Assets::Get().LoadFont("Content/Resources/Font/upheavtt.ttf", "hudfont");

	mHeads.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/head.png", "head", TextureFilter::NEAREST, false));
	mHeads.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/headLeft.png", "headLeft", TextureFilter::NEAREST, false));
	mHeads.push_back(clt::Assets::Get().LoadTexture("Content/Resources/Sprites/headRight.png", "headRight", TextureFilter::NEAREST, false));

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/mainHUD.png", "hudFrame", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("mainFrame", "hudFrame", 8, Vector2{ 0, -600 }, 50);
	GetCurrentWidget()->CreateElement<clt::TextElement>("healthText", std::to_string(mLife) + "%", "hudfont", Color::Red, 1.15f, Vector2{ -300, -280 }, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("armorText", "129%", "hudfont", Color::Red, 1.15f, Vector2{180, -280}, 100);

	GetCurrentWidget()->CreateElement<clt::TextElement>("ammoText", "55", "hudfont", Color::Red, 1.15f, Vector2{ -500, -280 }, 100);

	std::vector<clt::Texture*> weapon = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 5, "_playerShoot.png", "pistolShoot", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::AnimatorElement>("playerWeapon", "pistolShoot", weapon, false, 10, 4, Vector2{0, -300});

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("playerHead", mHeads[0],7.5, Vector2{0, -600}, 200);
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

	float currentTime = clt::Timer::GetTimeSinceLoad();

	if (currentTime > mTauntDelay)
	{
		float randomDelay = rand() % 2;

		mTauntDelay = currentTime + randomDelay;

		int random = rand() % 3;
		
		GetCurrentWidget()->GetElement<clt::SpriteElement>("playerHead")->SetTexture(mHeads[random]);
		
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

		Zombie* enemy = dynamic_cast<Zombie*>(hitResult.Actor);
		if (enemy)
		{
			enemy->GetHit();
		}
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

void DoomHUD::UpdateLife(int pNewLife)
{
	mLife = pNewLife;
	GetCurrentWidget()->GetElement<clt::TextElement>("healthText")->SetText(std::to_string(mLife) + "%");
}
