#include "DoomHUD.h"


DoomHUD::DoomHUD() : HUDComponent(), lifeState(5)
{
	CreateWidget<clt::UIPanel>("PlayerScreen");
}

void DoomHUD::Start()
{
	std::vector<clt::Texture*> weapon = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 4, "_playerShoot.png", "pistolShoot", TextureFilter::NEAREST);

	GetCurrentWidget()->CreateElement<clt::AnimatorElement>("playerWeapon", "pistolShoot", weapon, false, 5)->SetSize(3);
}

void DoomHUD::TriggerShoot()
{
	GetCurrentWidget()->GetElement<clt::AnimatorElement>("playerWeapon")->PlayAnim("pistolShoot");

	CLUTTER_LOG("pan");
}
