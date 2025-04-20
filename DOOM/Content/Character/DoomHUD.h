#include "Core/All.h"

enum class Weapons
{
	Hand,
	Pistol,
	ShotGun,
};

class DoomHUD : public clt::HUDComponent
{
public:
	int lifeState;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;

	void TriggerShoot();
};