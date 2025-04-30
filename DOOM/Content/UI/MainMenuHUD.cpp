#include "MainMenuHUD.h"

MainMenuHUD::MainMenuHUD() : HUDComponent()
{
	CreateWidget<clt::UIPanel>("mainMenu");
	CreateWidget<clt::UIPanel>("options");
}
