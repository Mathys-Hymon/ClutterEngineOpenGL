#include "DoomHUD.h"


DoomHUD::DoomHUD() : HUDComponent(), lifeState(5)
{
	CreateWidget<clt::UIPanel>("PlayerScreen");

	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/mainHUD.png", "hudFrame", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::SpriteElement>("mainFrame", "hudFrame", 8, Vector2{0, -600}, 100);

	std::vector<clt::Texture*> weapon = clt::Assets::Get().BulkLoadTexture("Content/Resources/Sprites/", 5, "_playerShoot.png", "pistolShoot", TextureFilter::NEAREST, false);

	GetCurrentWidget()->CreateElement<clt::AnimatorElement>("playerWeapon", "pistolShoot", weapon, false, 10, 4, Vector2{0, -300});
}

void DoomHUD::Start()
{

}

void DoomHUD::TriggerShoot()
{
	GetCurrentWidget()->GetElement<clt::AnimatorElement>("playerWeapon")->PlayAnim("pistolShoot");

	CLUTTER_LOG("pan");
}
