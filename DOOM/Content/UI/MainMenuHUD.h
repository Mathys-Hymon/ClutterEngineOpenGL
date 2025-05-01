#include "Core/All.h"

class MainMenuHUD : public clt::HUDComponent
{
public:
	MainMenuHUD();
	~MainMenuHUD() = default;

	void OpenGame();
};