#include "Core/All.h"

enum class Weapons
{
	Hand,
	Pistol,
	ShotGun,
};

class DoomHUD : public clt::HUDComponent
{
	float mCanShoot;
public:
	int mLifeState;

	DoomHUD();
	~DoomHUD() = default;

	virtual void Start() override;
	virtual void Update() override;

	void TriggerShoot();
};